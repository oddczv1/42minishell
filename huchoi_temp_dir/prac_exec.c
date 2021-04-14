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
    args = ft_split("cat", ' ');
    int input = open("test.txt", O_RDONLY);
    //int input = dup(0);
    if (0 == (p1 = fork()))
    {//close 꼭 해주기.
        close(fd[0]);
        dup2(fd[1], 1);
        dup2(input ,0);
        close(fd[1]);
        if (0 > execve("/bin/cat", args, NULL))
            ft_putstr_fd("err", 1);
        exit(0);
    }
    else
    {//close 꼭 해주기.
        /*int ret = close(fd[0]);
        printf("close test : %d\n", ret);
        ret = close(fd[1]);
        printf("close test : %d\n", ret); //p1에서 close된줄 알았는데 여기선 또 close가 안되어있다.*/
        args2 = ft_split("grep 05 ", ' ');
        //waitpid(p1, &status, 0);//여기서 이 함수 호출하면 안되나...?
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
        {//여기서도 마찬가지로 close 꼭 해주기
            close(fd[0]);
            close(fd[1]);
            waitpid(p1, &status, 0);
            waitpid(p2, &status, 0);//이 줄 위에서 안하고 밑에서 close해버리면 hang상태가 되어버림.
            //close를 44번줄 위에서 했다고 하더라고 행이 안되는건아니다. 다만 무한 행이 안되는것임. 그 차이는 명확히 할것.
            //hang이 된 이유 : write fd 가 적어도 하나이상 남아있어서, read가 write가 close될때 까지를 기다리는것. 
            //write fd가 close되면 hang상태가 풀림.
            ft_putstr_fd("reach!!", 1);
        }
    }
    return (0);
}