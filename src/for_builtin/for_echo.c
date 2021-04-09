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