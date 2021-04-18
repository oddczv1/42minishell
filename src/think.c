#include "../minishell.h"
#define CUR(X) ((X % 2) * (2))
//idx짝수->0, idx홀수->2
int     pipe_func(t_data *d, int *fx, int fd, int idx)
{
    pipe(&fx[CUR(idx)]);
    pid_t pid;
    int status;
    char exec_file[1024];
    char *temp;
    if (is_builtin(d))
    {
        //dup2(fd, 0);//이거 없애야할듯..? 빌트인 명령어는 표준입력 리다이렉션 하지 못하는게 팩트..
        dup2(fx[CUR(idx) + 1], 1);//
        process_builtin(d);
        close(fd);//
        //close(fx[CUR(idx)]);//이 부분이 문제엿음
        close(fx[CUR(idx) + 1]);
    }
    else if (is_exec_bin(d) || is_exec_usr(d))
    {
        if (0 == (pid = fork()))
        {
            dup2(fd, 0);
            dup2(fx[CUR(idx) + 1], 1);
            close(fd);
            close(fx[CUR(idx)]);
            close(fx[CUR(idx) + 1]);
            if (is_exec_bin(d))
            {
                temp = ft_strjoin("/bin/", d->cmd[0]);
                ft_strlcpy(exec_file, temp, ft_strlen(temp) + 1);
                free(temp);
                execve(exec_file, d->cmd, NULL);
            }
            else//is_exec_usr(d)
            {
                temp = ft_strjoin("/usr/bin/", d->cmd[0]);
                ft_strlcpy(exec_file, temp, ft_strlen(temp) + 1);
                free(temp);
                execve(exec_file, d->cmd, NULL);
            }
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
        }
    }
    else
    {
        ft_putstr_fd("zsh: command not found: ", 2);
		write(2, d->cmd[0], ft_strlen(d->cmd[0]));
        write(2, "\n", 1);
        return -1;
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
            ft_free(d->cmd);
            recover_std(d);
            return ;
        }
        ft_free(d->cmd);
        idx++;
    }
    ft_check_split(d, idx);
    dup2(fd, 0);
    //dup2() 앞단에서 표준출력에 대한 dup2(~~, 1); 처리 해줬을것... recover만 잘 시켜주자.
    close(fd);
    close(fx[CUR(idx-1)]);
    char *exec_file;
    if (is_builtin(d))
    {
        process_builtin(d);//이 부분이 조금 애매하긴한데... 뭔가 확신이 안생김.
        exit(0);
    }
    else if (is_exec_bin(d))
    {
        exec_file = ft_strjoin("/bin/", d->cmd[0]);
        execve(exec_file, d->cmd, NULL);
    }
    else if (is_exec_usr(d))
    {
        exec_file = ft_strjoin("/usr/bin/", d->cmd[0]);
        execve(exec_file, d->cmd, NULL);
    }
    else
    {
		ft_putstr_fd("zsh: command not found: ", 2);
		write(2, d->cmd[0], ft_strlen(d->cmd[0]));
        write(2, "\n", 1);
        //recover_std(d);
	}
    //ft_free(d->cmd);//어떤 경우로 이 process_pipe가 종료되든 이 함수 호출은 필수적이다. ***
    recover_std(d);
}