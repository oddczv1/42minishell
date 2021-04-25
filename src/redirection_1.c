/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:22:57 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 18:59:28 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_one_right(t_data *d, int *i)
{
	if (!d->cmd[(*i) + 1] || !ft_memcmp(d->cmd[(*i) + 1], ">", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], ">>", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], "<", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], "<<", 2))
	{
		ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
		g_t.status = 1;
		d->enable = 1;
		return (1);
	}
	if (d->fd[0] != 0)
	{
		close(d->fd[0]);
		close(d->fd[1]);
	}
	d->fd[0] = open(d->cmd[(*i) + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	d->fd[1] = dup(1);
	dup2(d->fd[0], 1);
	free(d->cmd[(*i)]);
	d->cmd[(*i)] = 0;
	ft_non_cmd(d, i);
	return (0);
}

int			ft_two_right(t_data *d, int *i)
{
	if (!d->cmd[(*i) + 1] || !ft_memcmp(d->cmd[(*i) + 1], ">", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], ">>", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], "<", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], "<<", 2))
	{
		ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
		g_t.status = 1;
		d->enable = 1;
		return (1);
	}
	if (d->fd[0] != 0)
	{
		close(d->fd[0]);
		close(d->fd[1]);
	}
	d->fd[0] = open(d->cmd[(*i) + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	d->fd[1] = dup(1);
	dup2(d->fd[0], 1);
	free(d->cmd[(*i)]);
	d->cmd[(*i)] = 0;
	ft_non_cmd(d, i);
	return (0);
}

void		ft_onf_left_2(t_data *d, int *i)
{
	if (d->fd[0] != 0)
	{
		dup2(d->ft_std[0], 0);
		close(d->fd[0]);
	}
	d->fd[0] = open(d->cmd[(*i) + 1], O_RDONLY);
}

int			ft_one_left(t_data *d, int *i)
{
	if (!d->cmd[(*i) + 1] || !ft_memcmp(d->cmd[(*i) + 1], ">", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], ">>", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], "<", 2)
		|| !ft_memcmp(d->cmd[(*i) + 1], "<<", 2))
	{
		ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
		g_t.status = 1;
		d->enable = 1;
		return (1);
	}
	ft_onf_left_2(d, i);
	if (d->fd[0] < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(d->cmd[(*i) + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_t.status = 1;
		d->enable = 1;
		recover_std(d);
		return (1);
	}
	dup2(d->fd[0], 0);
	ft_non_cmd(d, i);
	return (0);
}

void		ft_check_redirection(t_data *d)
{
	int i;

	d->start = 0;
	d->is_cflage = 0;
	d->is_cmd = 0;
	i = -1;
	while (d->cmd[++i])
	{
		if (ft_memcmp(d->cmd[i], ">", 2) == 0)
		{
			if (ft_one_right(d, &i))
				break ;
		}
		else if (ft_memcmp(d->cmd[i], ">>", 3) == 0)
		{
			if (ft_two_right(d, &i))
				break ;
		}
		else if (ft_memcmp(d->cmd[i], "<", 2) == 0)
		{
			if (ft_one_left(d, &i))
				break ;
		}
	}
	ft_put_cmd(d);
}
