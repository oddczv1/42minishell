#include "../minishell.h"

int main(void)
{
    pid_t p1, p2, p3;
    int ps = dup(1);
    int fd[4];
    int temp;
    char **arg1, **arg2, **arg3;
    arg1 = ft_split("ls -al", ' ');
    arg2 = ft_split("grep seoul", ' ');
    arg3 = ft_split("grep 27", ' ');
    pipe(&fd[0]);
    if (0 == (p1 = fork()))
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        if (0 > execve("/bin/ls", arg1, NULL))
            ft_putstr_fd("err", ps);
        exit(0);
    }
    else
    {
        pipe(&fd[2]);
        if (0 == (p2 = fork()))
        {
            dup2(fd[0], 0);
            dup2(fd[3], 1);//
            close(fd[3]);
            close(fd[2]);
            close(fd[0]);
            close(fd[1]);
            if (0 > execve("/usr/bin/grep", arg2, NULL))
                ft_putstr_fd("err", ps);    
            exit(0);
        }
        else
        {
            close(fd[0]);
            close(fd[1]);
            dup2(fd[2], 0);  
            wait(NULL);
            wait(NULL);
            if (0 == (p3 = fork()))
            {
                dup2(temp ,0);
                close(fd[2]);
                close(fd[3]);
                execve("/usr/bin/grep", arg3, NULL);
            }
            else
            {
                close(fd[2]);
                close(fd[3]);
                wait(NULL);
            }
        }
    }
}