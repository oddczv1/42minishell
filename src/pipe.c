/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:20:47 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/21 21:20:49 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		is_pipe(t_data *d)
{
	d->p_nb = 0;
	while (d->argv[d->p_nb])
		d->p_nb++;
	d->pids = malloc(sizeof(pid_t) * (d->p_nb + 1));
	g_t.flag = 1;
	if ((d->pids[d->p_nb] = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		process_pipe(d);
	}
	else
	{
		waitpid(d->pids[d->p_nb], &g_t.status, 0);
		g_t.status = WEXITSTATUS(g_t.status);
	}
}

void		non_pipe(t_data *d)
{
	d->p_j = -1;
	while (d->argv[++d->p_j])
	{
		ft_check_split(d, d->p_j);
		if (!d->enable)
			process(d);
		ft_free(d->cmd);
	}
}
