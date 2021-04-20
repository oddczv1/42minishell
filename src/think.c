#include "../minishell.h"
#define CUR(X) ((X % 2) * (2))
//idx짝수->0, idx홀수->2
int     pipe_func(t_data *d, int *fx, int fd, int idx)
{
    pipe(&fx[CUR(idx)]);
    //pid_t pid;
    //int status;
    if (is_builtin(d))
    {
        //dup2(fd, 0);//이거 없애야할듯..? 빌트인 명령어는 표준입력 리다이렉션 하지 못하는게 팩트.. 근데 이 부분 해줘도 문제는 없음.
        dup2(fx[CUR(idx) + 1], 1);//
        process_builtin(d);//d->status갱신 작업을 process_builtin함수에서 진행. 이미 status에 값이 0으로 초기화되었음을 기억..
        close(fd);
        //close(fx[CUR(idx)]);//이 부분이 문제엿음
        close(fx[CUR(idx) + 1]);
    }
    else if (get_exec_dir_file(d))
    {
        if (0 == (d->pids[idx] = fork()))
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
            if (idx != 0)//제일 초기단계만 아니면 이 조건문에서 참이됨.
            {
                close(fx[CUR(idx-1)]);
                close(fd);
            }
            //waitpid(pid, &status, 0);
            //if (WIFEXITED(status))
            //    d->status = WEXITSTATUS(status);
        }
    }
    else if (!d->status)
    {
        ft_putstr_fd("zsh: command not found: ", 2);
		write(2, d->cmd[0], ft_strlen(d->cmd[0]));
        write(2, "\n", 1);
        close(fx[CUR(idx)]);
        close(fx[CUR(idx) + 1]);
        close(fd);
        return (d->ft_std[0]);//여기서 status값 갱신하지 않고 다른데에서 갱신
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
    /*while (d->argv[idx])
        idx++;
    d->pids = (pid_t*)malloc(sizeof(pid_t) * idx);
    while(--idx >= 0)
        d->pids[idx] = 0;*/
    int fx[4];
    idx = 0;
    while (d->argv[idx + 1] != NULL)    
    {
        ft_check_split(d, idx);
        fd = pipe_func(d, fx, fd, idx);
        ft_free(d->cmd);
        idx++;
    }
    if (0 == (d->pids[idx] = fork()))
    {
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
            exit(127);
	    }
    }
    int count = idx;
    int temp_status;
	while (count >= 0)
	{
		waitpid(d->pids[count], &temp_status, 0);//여기서 반환된 상태값은 사용안될예정 (마지막 명령어의 상태값이 중요함.)
		if (count == (idx - 1))
		{
			d->status = WEXITSTATUS(temp_status);
		}
		count--;
	}
    exit(d->status);
}