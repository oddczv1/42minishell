#include "../minishell.h"

void	processed(void)
{
	char **cmd = ft_split("ls -ajl", ' ');
	int status;
	pid_t pid;
	pid_t p1;
	char		code;
	if (0 == (p1 = fork()))
	{
		execve("/bin/ls", cmd, NULL);
		//return (code);//return 이 맞을듯..? exit(code)가 맞으려나..?
		//execve("/bin/grep", cmd, NULL);
	}
	else
	{
		waitpid(p1, &status, 0);
		if (WIFEXITED(status))
			printf("exit status : %d\n", WEXITSTATUS(status));
	}
	return;
}

int main(void)
{
	processed();
}