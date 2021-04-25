/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:20:47 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/25 02:39:47 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		is_pipe(t_data *d)
{
	int status;

	d->p_nb = 0;
	while (d->argv[d->p_nb])
		d->p_nb++;
	d->pids = malloc(sizeof(pid_t) * (d->p_nb + 1));
	if ((d->pids[d->p_nb] = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		process_pipe(d);
	}
	else
	{
		g_t.pids = d->pids[d->p_nb];
		waitpid(d->pids[d->p_nb], &status, 0);
		if (status == 2)
			g_t.status = 130;
		else if (status == 3)
			g_t.status = 131;
		else
			g_t.status = WEXITSTATUS(status);
		free(d->pids);
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
		ft_cmd_free(d);
	}
}
