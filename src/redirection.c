/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:22:57 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 18:59:28 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_check_redirection_1(t_data *d, int i)
{
	while (d->cmd[++i])
	{
		if (ft_memcmp(d->cmd[i], "<", 2) == 0)
		{
			if (!d->cmd[i + 1])
			{
				ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
				g_t.status = 1;
				d->enable =1;
				break ;
			}
			d->fd[0] = open(d->cmd[i + 1], O_RDONLY);
			if (d->fd[0] < 0)
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(d->cmd[i + 1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_t.status = 1;
				d->enable = 1;
				break ;
			}
			dup2(d->fd[0], 0);
			d->cmd[i] = 0;
			break ;
		}
	}
}

void		ft_check_redirection_2(t_data *d, int i)
{
	while (d->cmd[++i])
	{
		if (ft_memcmp(d->cmd[i], ">", 2) == 0)
		{
			if (!d->cmd[i + 1])
			{
				ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
				g_t.status = 1;
				d->enable =1;
				break ;
			}
			d->fd[0] = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			d->fd[1] = dup(1);
			dup2(d->fd[0], 1);
			d->cmd[i] = 0;
			if (i == 0)
			{
				free(d->cmd[0]);
				d->cmd[0] = ft_strdup("echo");
				d->cmd[1] = 0;
			}
			break ;
		}
		else if (ft_memcmp(d->cmd[i], ">>", 3) == 0)
		{
			if (!d->cmd[i + 1])
			{
				ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
				g_t.status = 1;
				d->enable =1;
				break ;
			}
			d->fd[0] = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			d->fd[1] = dup(1);
			dup2(d->fd[0], 1);
			d->cmd[i] = 0;
			if (i == 0)
			{
				free(d->cmd[0]);
				d->cmd[0] = ft_strdup("echo");
				d->cmd[1] = 0;
			}
			break ;
		}
	}
}

void		ft_check_redirection(t_data *d)
{
	int i;

	i = -1;
	ft_check_redirection_1(d, i);
	ft_check_redirection_2(d, i);
}
