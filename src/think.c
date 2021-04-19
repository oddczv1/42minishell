#include "../minishell.h"
#define CUR(X) ((X % 2) * (2))
//idx짝수->0, idx홀수->2
int     pipe_func(t_data *d, int *fx, int fd, int idx)
{
    pipe(&fx[CUR(idx)]);
    pid_t pid;
    int status;
    if (is_builtin(d))
    {
        //dup2(fd, 0);//이거 없애야할듯..? 빌트인 명령어는 표준입력 리다이렉션 하지 못하는게 팩트.. 근데 이 부분 해줘도 문제는 없음.
        dup2(fx[CUR(idx) + 1], 1);//
        process_builtin(d);//d->status갱신 작업을 process_builtin함수에서 진행. 이미 status에 값이 0으로 초기화되었음을 기억..
        close(fd);//
        //close(fx[CUR(idx)]);//이 부분이 문제엿음
        close(fx[CUR(idx) + 1]);
    }
    else if (get_exec_dir_file(d))
    {
        if (0 == (pid = fork()))
        {
            dup2(fd, 0);
            dup2(fx[CUR(idx) + 1], 1);
            close(fd);
            close(fx[CUR(idx)]);
            close(fx[CUR(idx) + 1]);
            execve(d->exec_file, d->cmd, NULL);
        }
        else
        {
            close(fx[CUR(idx) + 1]);
            if (idx != 0)//제일 초기단계만 아니면 이 조건문에서 참이됨.
            {
                close(fx[CUR(idx-1)]);
                close(fd);
            }
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                d->status = WEXITSTATUS(status);
        }
    }
    else
    {
        ft_putstr_fd("zsh: command not found: ", 2);
		write(2, d->cmd[0], ft_strlen(d->cmd[0]));
        write(2, "\n", 1);
        return -1;//여기서 status값 갱신하지 않고 다른데에서 갱신
    }
    close(fx[CUR(idx) + 1]);
    if (idx != 0)//제일 초기단계만 아니면 이 조건문에서 참이됨.
    {
        close(fx[CUR(idx-1)]);
        close(fd);
    }
    return (fx[CUR(idx)]);
}

void    process_pipe(t_data *d)//recover_std함수 호출 필요없을듯.... 독립이니까
{
    int fd = dup(0);
    int idx = 0;
    int fx[4];
    while (d->argv[idx + 1] != NULL)
    {
        ft_check_split(d, idx);
        if (-1 == (fd = pipe_func(d, fx, fd, idx)))
        {
            if (d->status == 0)
            {
                ft_free(d->cmd);
                recover_std(d);
                //d->status = 127;//할 필요 없음
                exit(127);
            }
            else
                exit(d->status);
        }
        ft_free(d->cmd);
        idx++;
    }
    ft_check_split(d, idx);
    dup2(fd, 0);
    close(fd);
    close(fx[CUR(idx-1)]);
    if (is_builtin(d))
    {
        process_builtin(d);//status값의 갱신작업은 process_builtin 함수에서 진행. status=0으로 초기화되어있음을 기억...
        if (d->status != 0)
            exit(d->status);
    }
    else if (get_exec_dir_file(d))
        execve(d->exec_file, d->cmd, NULL);//얘안에 exit(code)가 들어있음.. (think.c 의 모든함수는 exit(code)로 끝나야함.)
    else
    {
		ft_putstr_fd("zsh: command not found: ", 2);
		write(2, d->cmd[0], ft_strlen(d->cmd[0]));
        write(2, "\n", 1);
        recover_std(d);
        ft_free(d->cmd);
        exit(127);
	}
    ft_free(d->cmd);//어떤 경우로 이 process_pipe가 종료될때 이 함수 호출은 필수적이다. 필요없음...
    recover_std(d);
    exit(0);
}