#include "../minishell.h"

void			over_write(t_data *data, char *key_value, int idx)
{
	char	*temp;
	char	*p;
	char	*str;

	if (add_operation(data->cmd[1]))
	{
		p = ft_strchr(data->cmd[1], '=');
		temp = ft_strdup(p + 1);
		str = ft_strjoin(data->env[idx], temp);
		free(temp);
		free(data->env[idx]);
		data->env[idx] = str;
	}
	else
	{
		free(data->env[idx]);
		data->env[idx] = ft_strdup(key_value);
	}
}

int				match_key(char *key_value, char *str)//검증필요
{
	int size;

	size = 0;
	while (key_value[size] != 0 && key_value[size] != '=')
		size++;
	if (key_value[size - 1] == '+')
		size--;
	if (!ft_strncmp(key_value, str, size - 1) && \
		(str[size] == '=' || str[size] == '\0'))
		return (TRUE);
	return (FALSE);
}

static	void	delete_one(t_data *data, char **new_env, char *key)
{
	int	idx;
	int	count;

	idx = 0;
	count = 0;
	while (data->env[idx])
	{
		if (match_key(key, data->env[idx]) == TRUE)
			free(data->env[idx++]);
		else
			new_env[count++] = data->env[idx++];
	}
	new_env[count] = NULL;
}

static	void	add_one(t_data *data, char **new_env, char *str)
{
	int idx;
	int count;

	idx = 0;
	count = 0;
	while (data->env[idx])
		new_env[count++] = data->env[idx++];
	if (ft_strchr(str, '='))
		new_env[count++] = ft_strdup(str);
	new_env[count] = NULL;
}

/*void			delete_equal(t_data *data)
{
	char	*str;
	char	*temp;
	char	*point;
	char	*plus;

	point = ft_strchr(data->cmd[1], '=');
	if (point != NULL)
		plus = ft_strdup(p + 1);
	//temp = ft_strdup(data->cmd[1]);
	str = ft_strjoin(data->env[idx], point + 1);
	free(temp);
	free(data->cmd[1]);
	data->cmd[1] = ft_strjoin(str, plus);
}*/

void			renewer_env(t_data *data, char *key, char *str, int size)
{
	char **new_env;

	new_env = malloc(sizeof(char *) * size);
	new_env[size - 1] = NULL;
	if (str == NULL)
		delete_one(data, new_env, key);
	else
	{
		/*if (add_operation(data->cmd[1]))
		{
			delete_equal(data);
		}*/
		add_one(data, new_env, str);
	}
	free(data->env);
	data->env = new_env;
}
