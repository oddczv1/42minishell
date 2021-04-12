#include "../minishell.h"
#include <stdio.h>

int main(void)
{
    int fd1 = open("test.txt", O_RDONLY);
    int fd2 = open("test.txt", O_RDONLY);
    int ret;
    ret= close(fd1);
    printf("test: %d\n", ret);
    ret= close(fd2);
    printf("test: %d\n", ret);
    return (0);
}