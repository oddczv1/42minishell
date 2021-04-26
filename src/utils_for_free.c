/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 02:51:01 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/25 02:51:23 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_free(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void		ft_cmd_free(t_data *d)
{
	int i;

	i = 0;
	while (i < g_t.max_idx)
	{
		if (d->cmd[i])
			free(d->cmd[i]);
		i++;
	}
	free(d->cmd);
}
