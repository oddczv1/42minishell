/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:39:26 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:45:21 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_builtin(t_data *d, int *fx, int fd, int idx)
{
	dup2(fd, 0);
	dup2(fx[cur(idx) + 1], 1);
	close(fd);
	close(fx[cur(idx)]);
	close(fx[cur(idx) + 1]);
	process_builtin(d);
	exit(g_t.status);
}

void	process_single_builtin(t_data *d, int *fx, int fd, int idx)
{
	if (0 == (d->pids[idx] = fork()))
		single_builtin(d, fx, fd, idx);
	else
	{
		if (idx != 0)
			close(fd);
	}
}

void	process_single_exec(t_data *d, int *fx, int fd, int idx)
{
	if (0 == (d->pids[idx] = fork()))
	{
		ready_for_execute(fx, fd, idx);
		execve(d->exec_file, d->cmd, d->env);
	}
	else
	{
		if (idx != 0)
			close(fd);
	}
}
