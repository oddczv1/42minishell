#include "../minishell.h"

int main(void)
{
	char **arg = ft_split("sleep 3 | ls -ajl", '|');
	char **cmd;
	int status;
	t_data d;
	pid_t p[4];
	int nb = 0;
	while (nb < 3)
		p[nb++] = 0;
	int fd[2];
	pipe(fd);
	if (0 == (p[0] = fork()))
	{
		cmd = ft_split(arg[0], ' ');
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve("/bin/sleep", cmd, 0);
	}
	else
	{
		close(fd[1]);
		//waitpid(p1, &status, 0);
		if (0 == (p[1] = fork()))
		{
			cmd = ft_split(arg[1], ' ');
			dup2(fd[0], 0);
			close(fd[0]);
			execve("/bin/ls", cmd, 0);
		}
		/*else
		{
			waitpid(p2, &status, 0);
		}*/
	}
	int i = 0;
	while (i <= 3)
	{
		waitpid(p[i], &status, 0);
		if (i == 1)
			d.status = WEXITSTATUS(status);
		i++;
	}
	printf("test : %d\n", d.status);
	//waitpid(p[0], &status, 0);
	//waitpid(p[1], &status, 0);
	return (0);
}