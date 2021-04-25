/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:16 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/25 19:57:22 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	error_message(t_data *data)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	write(2, data->cmd[1], ft_strlen(data->cmd[1]));
	write(2, "\n", 1);
	g_t.status = 1;
}

void			process_cd(t_data *data)
{
	int		idx;
	char	buf[1025];

	idx = 0;
	if (data->cmd[1] == NULL)
	{
		free(data->cmd[0]);
		free(data->cmd);
		data->cmd = ft_split("cd ~", ' ');
	}
	if (ft_strncmp(data->cmd[1], "~", 2) == 0)
	{
		while (data->env[idx])
		{
			if (match_key("HOME", data->env[idx++]) == TRUE)
				get_value(data->env[idx - 1], buf);
		}
		free(data->cmd[1]);
		data->cmd[1] = ft_strdup(buf);
	}
	char **split = ft_split(data->cmd[1], '/');
	idx = 0;
	while (split[idx])
	{
		if (-1 == chdir(split[idx]))
			error_message(data);
		idx++;
	}
	idx = 0;
	while (split[idx])
		free(split[idx++]);
	free(split);//필수!!!!
	recover_std(data);
}
