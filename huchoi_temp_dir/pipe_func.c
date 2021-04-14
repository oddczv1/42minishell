#include "../minishell.h"

int		pipe_func(t_data *data, int fd)
{
	pid_t pid;
	int ret;
	if (0 == (pid =fork()))
	{

	}
	else
	{

	}
	return (ret);
}
int main(void)
{
	t_data data;
	data.argv = ft_split("ls -al | grep seoul | grep 42 | grep 1", ' ');
	int idx = 0;
	int fd = 0;
	pid_t pid;
	if (0 == (pid = fork()))
	{
		while (data.argv[idx])
		{
			fd = pipe_func(&data, fd);
			idx++;
		}
	}
}