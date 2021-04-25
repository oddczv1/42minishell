/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:33:49 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 18:59:26 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_get_cmdlen(t_data *d)
{
	d->max_idx = -1;
	while (d->cmd[++d->max_idx])
		;
}

int			ft_check_escape_num(char *str, int i)
{
	int num;

	num = 0;
	if (str[i] == '\'' || str[i] == '\"' || str[i] != '\\')
	{
		while (str[--i] == '\\')
			++num;
	}
	g_t.rs_len = num;
	num = num % 2;
	return (num);
}

int			ft_read_str(t_data *d, char *buf)
{
	char *tem;

	if (!(tem = ft_strjoin(d->str, buf)))
		return (0);
	if (d->str)
		free(d->str);
	d->str = tem;
	return (1);
}

int			ft_isquote(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			return (-1);
	}
	return (1);
}

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
