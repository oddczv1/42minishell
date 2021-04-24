/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:34:53 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/24 15:44:26 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_builtin(t_data *d, int *fx, int fd, int idx)
{
	dup2(fx[cur(idx) + 1], 1);
	process_builtin(d);
	close(fd);
	close(fx[cur(idx) + 1]);
}

int		pipe_func(t_data *d, int *fx, int fd, int idx)
{
	pipe(&fx[cur(idx)]);
	if (is_builtin(d))
		single_builtin(d, fx, fd, idx);
	else if (get_exec_dir_file(d))
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
	else if (!d->flag)
	{
		err_messag(d, fx, fd, idx);
		return (d->ft_std[0]);
	}
	close(fx[cur(idx) + 1]);
	if (idx != 0)
		close(fd);
	return (fx[cur(idx)]);
}

void	connect_pipe(t_data *d, int *idx, int *fx, int *fd)
{
	*idx = 0;
	*fd = dup(0);
	while (d->argv[*idx + 1] != NULL)
	{
		ft_check_split(d, *idx);
		*fd = pipe_func(d, fx, *fd, *idx);
		ft_free(d->cmd);
		(*idx)++;
	}
}

void	last_command(t_data *d, int *fd, int *fx, int *idx)
{
	ft_check_split(d, *idx);
	dup2(*fd, 0);
	close(*fd);
	close(fx[cur(*idx - 1)]);
	if (d->enable != 0)
		exit(g_t.status);
	if (is_builtin(d))
		process_builtin(d);
	else if (get_exec_dir_file(d))
		execve(d->exec_file, d->cmd, d->env);
	else if (!d->flag)
		err_message(d);
	else if (g_t.status)
		exit(g_t.status);
}

void	process_pipe(t_data *d)
{
	int fd;
	int idx;
	int fx[4];
	int count;
	int temp_status;

	connect_pipe(d, &idx, fx, &fd);
	if (0 == (d->pids[idx] = fork()))
		last_command(d, &fd, fx, &idx);
	count = idx;
	while (count >= 0)
	{
		waitpid(d->pids[count], &temp_status, 0);
		if (count == (idx))
			g_t.status = WEXITSTATUS(temp_status);
		count--;
	}
	exit(g_t.status);
}
