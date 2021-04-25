/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:28:37 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:29:12 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				match_key(char *key_value, char *str)
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

void			renewer_env(t_data *data, char *key, char *str, int size)
{
	char **new_env;

	new_env = malloc(sizeof(char *) * size);
	new_env[size - 1] = NULL;
	if (str == NULL)
		delete_one(data, new_env, key);
	else
		add_one(data, new_env, str);
	free(data->env);
	data->env = new_env;
}
