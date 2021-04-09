#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>//for wait function
#include "minishell.h"
int check_apos(char *str);
void	process_builtin(t_data *data)
{
	char *buf;
	int idx;
	getcwd(buf, 100);
	chdir("/root");
	if (!ft_strcmp(data.cmd[0], "echo", ft_strlen("echo") + 1))
	{
		//write() printf() getenv() 
		//find_apos(char *str)
		idx = 1;
		while (cmd[idx])
		{
			ft_putstr_fd(cmd[0] + check_apos(cmd[0]), 1);
			idx++;
		}
	}
	else if (!ft_strcmp(data.cmd[0], "pwd", ft_strlen("pwd") + 1))
	{

	}
	else if (!ft_strcmp(data.cmd[0], "env", ft_strlen("env") + 1))
	{

	}
	else
	{

	}
}

void	process_bin(t_data *data)
{
	int status;
	pid_t pid;
	int fd[2];

	pipe(fd);
	if ((pid = fork()) == 0)
	{
		execve("/bin/bash", cmd, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return ;
}