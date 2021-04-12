#include "../minishell.h"
#include <stdio.h>

int main(void)
{
    pid_t p1, p2;
    char **args;
    char **args2;
    int status;
    int fd[2];
    pipe(fd);
    args = ft_split("ls -al", ' ');
    if (0 == (p1 = fork()))
    {//close 꼭 해주기.
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        if (0 > execve("/bin/ls", args, NULL))
            ft_putstr_fd("err", 1);
        exit(0);
    }
    else
    {//close 꼭 해주기.
        /*int ret = close(fd[0]);
        printf("close test : %d\n", ret);
        ret = close(fd[1]);
        printf("close test : %d\n", ret); //p1에서 close된줄 알았는데 여기선 또 close가 안되어있다.*/
        args2 = ft_split("grep seoul ", ' ');
        if (0 == (p2 = fork()))
        {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            if (0 > execve("/usr/bin/grep", args2, NULL))
                ft_putstr_fd("err", 1);
            exit(0);
        }
        else
        {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
    return (0);
}