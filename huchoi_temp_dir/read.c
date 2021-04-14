#include "../minishell.h"

int main(void)
{
    char **arg1 = ft_split("ls -al", ' ');
    char **arg2 = ft_split("grep t", ' ');
    char **arg3 = ft_split("grep t", ' ');
    pid_t p1,p2,p3;
    int fd[2];
    pipe(fd);
    int status;
    if (0 == (p2 = fork()))
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execve("/bin/ls", arg1, NULL);
    }
    else
    {
        waitpid(p2, &status, 0);
        if (0 == (p2 = fork()))
        {
            dup2(fd[0], 0);
            //dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            execve("/usr/bin/grep", arg2, NULL);
        }
        else
        {
            close(fd[1]);
            waitpid(p2, &status, 0);
            /*if (0 == (p3 = fork()))//이 블록 주석 해제하셨으면 25번줄 주석도 해제 하셔야 합니다.
            {
                dup2(fd[0], 0);
                close(fd[0]);
                execve("/usr/bin/grep", arg3, NULL);
            }
            else
            {
                waitpid(p3, &status, 0);
            }*/
        }
    }
}