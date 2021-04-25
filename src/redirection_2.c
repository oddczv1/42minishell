/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:52:10 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/25 03:52:13 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_iscmd(t_data *d, int i)
{
	if (d->cmd[i])
	{
		if (ft_memcmp(d->cmd[i], "<", 2) && ft_memcmp(d->cmd[i], ">", 2)
			&& ft_memcmp(d->cmd[i], ">>", 2))
			return (1);
	}
	else
		return (1);
	if (d->is_cmd == 1)
		return (1);
	return (0);
}

void		ft_non_cmd(t_data *d, int *i)
{
	if ((*i) == 0)
	{
		free(d->cmd[0]);
		d->cmd[0] = ft_strdup("echo");
		d->is_cflage = 1;
	}
	if (d->is_cflage == 1)
	{
		d->is_cmd = ft_iscmd(d, (*i) + 2);
		if (d->is_cmd == 1)
		{
			d->start = (*i) + 2;
			d->is_cflage = 2;
		}
	}
	else if (d->is_cflage == 0)
		ft_have_cmd(d, i);
}

void		ft_have_cmd(t_data *d, int *i)
{
	d->is_cmd = ft_iscmd(d, (*i) + 2);
	if (d->is_cmd == 1 && d->cmd[(*i) + 2])
	{
		d->start = (*i) + 2;
		while (d->cmd[(*i) + 2])
		{
			d->check_open = open(d->cmd[(*i) + 2], O_RDONLY);
			if (d->check_open < 0)
			{
				ft_putstr_fd(d->cmd[0], 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(d->cmd[(*i) + 2], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_t.status = 1;
				d->enable = 1;
				recover_std(d);
			}
			close(d->check_open);
			(*i)++;
		}
		ft_put_echo(d);
	}
}

void		ft_put_echo(t_data *d)
{
	char *temp;
	char *str;

	free(d->cmd[0]);
	d->cmd[0] = ft_strdup("echo");
	free(d->cmd[1]);
	d->cmd[1] = ft_strdup("-n");
	free(d->cmd[2]);
	d->cmd[2] = ft_strdup("");
	while (d->cmd[d->start])
	{
		temp = ft_strjoin(d->cmd[d->start], "\n");
		free(d->cmd[d->start]);
		d->cmd[d->start] = 0;
		str = ft_strjoin(d->cmd[2], temp);
		free(temp);
		free(d->cmd[2]);
		d->cmd[2] = str;
		++d->start;
	}
	d->cmd[3] = 0;
}

void		ft_put_cmd(t_data *d)
{
	int i;

	i = 0;
	if (d->is_cflage > 0)
	{
		free(d->cmd[1]);
		d->cmd[1] = NULL;
		if (d->cmd[d->start] != 0)
		{
			while (d->cmd[d->start] && ft_iscmd(d, d->start))
			{
				if (d->cmd[i] != NULL)
				{
					free(d->cmd[i]);
					d->cmd[i] = NULL;
				}
				d->cmd[i] = d->cmd[d->start];
				d->cmd[d->start] = NULL;
				i++;
				d->start++;
			}
			free(d->cmd[i]);
			d->cmd[i] = 0;
		}
	}
}
