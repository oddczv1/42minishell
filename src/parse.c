/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:45:09 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/09 23:45:12 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_check_argv(char *str)
{
	str[0] = 'h';
}

void        parse(t_data *d)
{
    int i;
    int j;

	i = -1;
	d->cmds = ft_split_semi(d->str);
	while (d->cmds[++i])
	{
		d->argv = ft_split_pipe(d->cmds[i]);
		j = -1;
		while (d->argv[++j])
		{
			ft_check_argv(d->argv[j]);
			//d->cmd = ft_split_space(d->argv[j]);
			//ft_command(&d);
				
        }
    }
}