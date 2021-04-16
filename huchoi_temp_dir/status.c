#include "../minishell.h"

int main(void)
{
	char **cmd = ft_split("grep -al", ' ');
	int status;
	pid_t pid;
	char		code;
	if (0 == (pid = fork()))
	{
		if (0 > (code = execve("/bin/grep", cmd, NULL)))
			return (code);//return 이 맞을듯..? exit(code)가 맞으려나..?
		//execve("/bin/grep", cmd, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("exit status : %d\n", WEXITSTATUS(status));
	}
	return (0);
}