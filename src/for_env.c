/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:28:15 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:28:17 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_value(char *str, char *buf)
{
	char	*p;

	p = ft_strchr(str, '=');
	ft_strlcpy(buf, p + 1, 1024);
}

int		findenv(t_data *data, char *buf)
{
	int		idx;
	char	*key;

	idx = 0;
	key = data->cmd[1];
	while (data->env[idx])
	{
		if (match_key(key, data->env[idx]) == TRUE)
		{
			get_value(data->env[idx], buf);
			return (1);
		}
	}
	return (-1);
}

int		delete_env(t_data *data, char *key)
{
	int idx;

	idx = 0;
	while (data->env[idx])
		idx++;
	renewer_env(data, key, NULL, idx + 1 - 1);
	return (1);
}

int		add_env(t_data *data, char *key_value)
{
	int idx;

	idx = 0;
	while (data->env[idx])
	{
		if (match_key(key_value, data->env[idx]) == TRUE)
		{
			over_write(data, key_value, idx);
			break ;
		}
		idx++;
	}
	if (data->env[idx] == NULL)
		renewer_env(data, NULL, data->cmd[1], idx + 1 + 1);
	return (1);
}

void	process_env(t_data *data)
{
	int idx;

	if (data->cmd[1] == NULL)
	{
		idx = 0;
		while (data->env[idx])
		{
			ft_putstr_fd(data->env[idx], 1);
			ft_putstr_fd("\n", 1);
			idx++;
		}
	}
	recover_std(data);
}
