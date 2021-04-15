#include "../minishell.h"

void	delete_last_newline(char **cmd)
{
	int idx = 0;
	while (cmd[idx])
		idx++;
	char *str = cmd[idx - 1];
	idx = 0;
	while (str[idx])
		idx++;
	if (str[idx - 1] == '\n')
		str[idx] = '\0';
}

int		is_newline(char *str)
{
	int idx = 0;
	while (str[idx])
		idx++;
	if (str[idx - 1] == '\n')
		return (1);
	return (0);
}

void	my_putstr_fd(char *str, int fd)
{
	int idx = 0;
	while (str[idx])
	{
		if (!ft_strncmp(&str[idx], "\\n", 2))
		{
			write(1, "\n", 1);
			idx+=2;
		}
		else if (!ft_strncmp(&str[idx], "\\f", 2))
		{
			write(1, "\f", 1);
			idx+=2;
		}
		else if (!ft_strncmp(&str[idx], "\\t", 2))
		{
			write(1, "\t", 1);
			idx+=2;
		}
		else if (!ft_strncmp(&str[idx], "\\v", 2))
		{
			write(1, "\v", 1);
			idx+=2;
		}
		else if (!ft_strncmp(&str[idx], "\\r", 2))
		{
			write(1, "\r", 1);
			idx+=2;
		}
		else
		{
			write(fd, &str[idx], 1);
			idx++;
		}
	}
}

void	porcess_echo(t_data *data)
{
	int idx = 1;
	if (data->cmd[1] == NULL)
	{
		write(1,"\n", 1);
		return ;
	}
	if (!ft_strncmp(data->cmd[idx], "-n", 3))
		idx++;
	while (data->cmd[idx + 1] && data->cmd[idx])
	{
		my_putstr_fd(data->cmd[idx], 1);//하나씩 write하다보니까 개행을 출력하지 못하는 문제가 발생. 따라서 my_putstr_fd 함수 생성.
		idx++;
		ft_putstr_fd(" ", 1);
	}
	if (ft_strncmp(data->cmd[1], "-n", 3) != 0)
	{
		my_putstr_fd(data->cmd[idx], 1);
		write(1, "\n", 2);
	}
	else//-n옵션 있을때 %개행처리? 이거 어떻게 하는건지..?
	{
		if (0 == fork())
		{
			my_putstr_fd(data->cmd[idx], 1);
		}
		else
			wait(NULL);
	}
	recover_std(data);
}
