#include "../minishell.h"

/*int check_apos(char *str)
{
	int size = ft_strlen(str);
	int start = 0;
	if (str[0] == '\"' || str[0] == '\'')
	{
		start = 1;
		if (str[size - 1] == str[0])
			str[size - 1] = '\0';
	}
	return (start);
}*/

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
			//write(fd, &str[idx], 2);
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