#include "../minishell.h"

int check_apos(char *str)
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
}

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