#include "../minishell.h"

int main(void)
{
    pid_t p1, p2;
    int fd[4];
    int count = 0;
    int status;
    pipe(&fd[0]);
    char **arg1, **arg2, **arg3, **arg4;
    arg1 = ft_split("ls -al", ' ');
    arg2 = ft_split("grep seoul", ' ');
    arg3 = ft_split("grep test", ' ');
    arg4 = ft_split("grep test.txt", ' ');
    if (0 == (p1 = fork()))
    {
        close(fd[(count % 2) * 2]);
        dup2(fd[((count % 2) * 2)] + 1, 1);
        close(fd[((count % 2) * 2) + 1]);
        execve("/bin/ls", arg1, NULL);
    }
    else
    {
        waitpid(p1, &status, 0);
        //ft_putstr_fd("reach??",1);
        count++;
        pipe(&fd[(count % 2) * 2]);
        if (0 == (p2 = fork()))
        {
            dup2(fd[((count-1) % 2) * 2], 0);
            dup2(fd[((count % 2) * 2) + 1], 1);
            close(fd[0]);
            close(fd[1]);
            close(fd[2]);
            close(fd[3]);
            execve("/usr/bin/grep", arg2, NULL);
        }
        else
        {
            close(fd[((count-1) % 2) * 2]);//사용(x) 상속 끝난 파이프파일 닫아주는거.
            close(fd[(((count-1) % 2) * 2) + 1]);//상속 끝나는 시점 외우자 else영역안에 else직후.
            waitpid(p2, &status, 0);
            count++;
            pipe(&fd[(count % 2) * 2]);//이전의 파이프파일 없어졌으니 질량보존으로 새로운 파이프파일 생성해줘야함.
            //위에 없어진 파이프파일 그대로 생성하는 그런 느낌임.
            if (0 == (p1 = fork()))
            {
                dup2(fd[(((count - 1) % 2) * 2)], 0);
                dup2(fd[((count % 2) * 2) + 1], 1);
                close(fd[0]);
                close(fd[1]);
                close(fd[2]);
                close(fd[3]);
                execve("/usr/bin/grep", arg3, NULL);
            }
            else
            {
                close(fd[(((count - 1) % 2) * 2)]);//-1
                close(fd[(((count - 1) % 2) * 2) + 1]);//-1
                waitpid(p1, &status, 0);
                dup2(fd[((count%2) * 2)], 0);
                close(fd[(count % 2) * 2]);
                close(fd[((count % 2) * 2) + 1]);
                execve("/usr/bin/grep", arg4, NULL);//쉘프로그램에서 서브쉘 만드는게 맞겠다....!(마지막이 execute로 끝나버리니까 라고 정리하는게 맞을듯.)
            }
        }
    }
}