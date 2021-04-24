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
int			ft_iscmd(t_data *d, int i)
{
	while (d->cmd[i])
	{
		 if (!ft_memcmp(d->cmd[i], "<", 2) || !ft_memcmp(d->cmd[i], ">", 2) || !ft_memcmp(d->cmd[i], ">>", 2))
			 return (1);
		 ++i;
	}
	return (0);
}

void		ft_check_redirection(t_data *d)
{
	int checkerr;
	int i;
	int j;
	int k;

	j = 0;
	i = -1;
	d->is_cflage = 0;
	d->is_cmd = 0;
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
			if (d->fd[0] != 0)
			{
				close(d->fd[0]);
				close(d->fd[1]);
			}
			d->fd[0] = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			d->fd[1] = dup(1);
			dup2(d->fd[0], 1);
			d->cmd[i] = 0;
			if (i == 0)
			{
				free(d->cmd[0]);
				d->cmd[0] = ft_strdup("echo");
				d->is_cflage = 1;
			}
			if (d->is_cflage == 1)
			{
				d->is_cmd = ft_iscmd(d, i + 2);
				if (d->is_cmd == 0)
					j = i + 2;
			}
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
			if (d->fd[0] != 0)
			{
				close(d->fd[0]);
				close(d->fd[1]);
			}
			d->fd[0] = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			d->fd[1] = dup(1);
			dup2(d->fd[0], 1);
			d->cmd[i] = 0;
			if (i == 0)
			{
				free(d->cmd[0]);
				d->cmd[0] = ft_strdup("echo");
				d->is_cflage = 1;
			}
			if (d->is_cflage == 1)
			{
				d->is_cmd = ft_iscmd(d, i + 2);
				if (d->is_cmd == 0)
					j = i + 2;
			}
		}
		else if (ft_memcmp(d->cmd[i], "<", 2) == 0)
		{
			
			if (!d->cmd[i + 1])
			{
				ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
				g_t.status = 1;
				d->enable =1;
				break ;
			}
			if (d->fd[0] != 0)
			{
				dup2(d->ft_std[0], 0);
				close(d->fd[0]);
			}
			d->fd[0] = open(d->cmd[i + 1], O_RDONLY);
			if (d->fd[0] < 0)
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(d->cmd[i + 1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_t.status = 1;
				d->enable = 1;
				recover_std(d);
				break ;
			}
			dup2(d->fd[0], 0);				
			if (i == 0)
			{
				free(d->cmd[0]);
				d->cmd[0] = ft_strdup("echo");
				d->is_cflage = 1;
			}
			if (d->is_cflage == 1)
			{
				d->is_cmd = ft_iscmd(d, i + 2);
				if (d->is_cmd == 0)
					j = i + 2;
			}
			else
			{	
				d->is_cmd = ft_iscmd(d, i + 2);
				if (d->is_cmd == 0 && d->cmd[i + 2])
				{
					j = i + 2;
					while (d->cmd[i + 2])
					{
						checkerr = open(d->cmd[i + 2], O_RDONLY);
						if (checkerr < 0)
						{				
							ft_putstr_fd(d->cmd[0], 2);					
							ft_putstr_fd(": ", 2);
							ft_putstr_fd(d->cmd[i + 2], 2);
							ft_putstr_fd(": No such file or directory\n", 2);
							g_t.status = 1;
							d->enable = 1;
							recover_std(d);
						}
						close(checkerr);
						i++;
					}
					free(d->cmd[0]);
					d->cmd[0] = ft_strdup("echo");
					free(d->cmd[1]);
					d->cmd[1] = ft_strdup("-n");
					char *temp;
					char *str;
					free(d->cmd[2]);
					d->cmd[2] = ft_strdup("");
					while (d->cmd[j])
					{
						temp = ft_strjoin(d->cmd[j], "\n");
						free(d->cmd[j]);//ㅇㅐ매..
						str = ft_strjoin(d->cmd[2], temp);
						free(temp);
						free(d->cmd[2]);
						d->cmd[2] = str;
						++j;
					}
					d->cmd[3] = 0;
				}
			}
		}
	}
	k = 0;
	if (d->is_cflage == 1)
	{
		d->cmd[1] = ft_strdup("");
		if (d->cmd[j] != 0)
		{
			while (d->cmd[j])
			{
				free(d->cmd[k]);
				d->cmd[k] = d->cmd[j];
				k++;
				j++;
			}
			d->cmd[k] = 0;
		}
	}	
}
