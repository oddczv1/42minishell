#include "../minishell.h"
#define CUR(X) ((X % 2) * (2))
//idx짝수->0, idx홀수->2
int     pipe_func(t_data *data, int *fx, int fd, int idx)
{
    pipe(&fx[CUR(idx)]);
    pid_t pid;
    int status;
    if (0 == (pid = fork()))
    {
        dup2(fd, 0);
        dup2(fx[CUR(idx) + 1], 1);
        close(fd);
        close(fx[CUR(idx)]);
        close(fx[CUR(idx) + 1]);
        if (data->cmd[0][0] == 'l')
            execve("/bin/ls", data->cmd, NULL);
        else
            execve("/usr/bin/grep", data->cmd, NULL);
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
    return (fx[CUR(idx)]);
}
void    process_pipe(t_data *d)
{
    int fd = dup(0);
    int idx = 0;
    int fx[4];
    while (d->argv[idx + 1] != NULL)
    {
        ft_check_argv(d->argv[idx]);
		d->cmd = ft_split_pipe(d->argv[idx]);
		ft_check_env(d);
		ft_remove_mark(d);							
		ft_check_redirection(d);
        fd = pipe_func(d, fx, fd, idx);
        idx++;
    }
    ft_check_argv(d->argv[idx]);
	d->cmd = ft_split_pipe(d->argv[idx]);
	ft_check_env(d);
	ft_remove_mark(d);							
	ft_check_redirection(d);
    dup2(fd, 0);
    close(fd);
    close(fx[CUR(idx-1)]);
    //char *exec_file;
    if (d->cmd[0][0] == 'l')
        execve("/bin/ls", d->cmd, NULL);
    else
        execve("/usr/bin/grep", d->cmd, NULL);
    /*if (is_builtin(d))
        process_builtin(d);//이 부분이 조금 애매하긴한데... 뭔가 확신이 안생김.
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
        ft_putstr_fd("error in piped...", 2);*/
}