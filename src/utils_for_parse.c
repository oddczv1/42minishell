/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_for_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:44:04 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 21:44:06 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_check_upper(t_data *d)
{
	int i;

	i = 0;
	while (d->cmd[0][i])
	{
		d->cmd[0][i] = ft_tolower(d->cmd[0][i]);
		i++;
	}
}

int     ft_check_escape_num(char *str, int i)
{
    int num;

    num = 0;
    if (str[i] == '\'' || str[i] == '\"')
    {
        while(str[--i] == '\\')
            ++num;
    }
    num = num % 2;
    return (num);
}

int			ft_isquote(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			return (1);
	}
	return (0);
}