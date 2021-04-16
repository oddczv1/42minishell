#include "../minishell.h"

void	processed(int *test)
{
	char **cmd = ft_split("aaaaa -al", ' ');
	//int status;
	pid_t pid;
	pid_t p1;
	char		code;
	if (0 == (p1 = fork()))
	{
		execve("/bin/usr/grep", NULL, NULL);
		//return (code);//return 이 맞을듯..? exit(code)가 맞으려나..?
		//execve("/bin/grep", cmd, NULL);
	}
	else
	{
		waitpid(p1, test, 0);
	}
	return;
}

int main(void)
{
	int test;
	processed(&test);
	printf("exit status : %d\n", WEXITSTATUS(test));
}