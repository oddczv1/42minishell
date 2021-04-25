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

void	err_messag(t_data *d, int *fx, int fd, int idx)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(d->cmd[0], 2);
	ft_putstr_fd(": command not found", 2);
	write(2, "\n", 1);
	close(fx[cur(idx)]);
	close(fx[cur(idx) + 1]);
	close(fd);
}

int		err_message(t_data *d)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(d->cmd[0], 2);
	ft_putstr_fd(": command not found", 2);
	write(2, "\n", 1);
	exit(127);
}

void	ready_for_execute(int *fx, int fd, int idx)
{
	dup2(fd, 0);
	dup2(fx[cur(idx) + 1], 1);
	close(fd);
	close(fx[cur(idx)]);
	close(fx[cur(idx) + 1]);
}

int		cur(int x)
{
	return ((x % 2) * (2));
}
