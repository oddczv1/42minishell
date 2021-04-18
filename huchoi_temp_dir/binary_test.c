#include <stdio.h>
#include "../minishell.h"
int main(void)
{
    pid_t p1, p2;
    int fd[2];
    char **cmd = ft_split("grep test", ' ');
    char buf[111];
    int status;
    ft_strlcpy(buf, "testing binary", 1000);
    pipe(fd);
    if (0 == (p1 = fork()))
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        write(1, buf, 10);
    }
    else
    {
        close(fd[1]);
        waitpid(p1, &status, 0);
        if (0 == (p2 = fork()))
        {
            dup2(fd[0], 0);
            close(fd[0]);
            execve("/usr/bin/grep", cmd, NULL);
        }
        else
        {
            close(fd[0]);
            waitpid(p2, &status, 0);
        }
    }
    return (0);
}