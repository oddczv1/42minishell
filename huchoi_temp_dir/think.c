#include "../minishell.h"
#define CUR(X) ((X % 2) * (2))
//idx짝수->0, idx홀수->2
#define BEFORE
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
int     main_func(t_data *data)
{
    //t_data data;
    //data.argv = ft_split("ls -al | grep test | grep testing", '|');
    int fd = dup(0);
    int idx = 0;
    int fx[4];
    while (data.argv[idx + 1] != NULL)
    {
        data.cmd = ft_split(data.argv[idx], ' ');
        fd = pipe_func(&data, fx, fd, idx);
        idx++;
    }
    pid_t pid;
    int status;
    data.cmd = ft_split(data.argv[idx], ' ');
    if (0 == (pid = fork()))
    {
        dup2(fd, 0);//표준출력 리다이렉션은 하지않음.
        close(fd);
        close(fx[CUR(idx-1)]);
        if (data.cmd[0][0] == 'l')
            execve("/bin/ls", data.cmd, NULL);
        else
            execve("/usr/bin/grep", data.cmd, NULL);
    }
    else
    {
        close(fd);
        close(fx[CUR(idx-1)]);
        waitpid(pid, &status, 0);
    }
}