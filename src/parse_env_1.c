/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:12:40 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/21 22:44:23 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_check_env_rs(char *str, int *j)
{
	if (str[*j] == '$' && str[(*j) - 1] == '\\')
	{
		ft_memmove(str + (*j) - 1, str + (*j), ft_strlen(str + (*j)));
		str[ft_strlen(str) - 1] = 0;
	}
	else
		(*j)++;
}

void		ft_put_env_2(t_data *d, char *str, int *i)
{
	int start;

	(*i)++;
	start = *i;
	while (str[*i] && !(str[(*i) - 1] != '\\' && str[*i] == '}'))
		(*i)++;
	if (!str[*i])
	{
		ft_putstr_fd("Non finished braceparam\n", 2);
		g_t.status = 1;
		d->enable = 1;
	}
	else
		ft_put_env_value_2(d, str, i, start);
}

void		ft_put_env_1(char *str, int *i)
{
	ft_memmove(str + (*i) - 1, str + (*i) + 1, ft_strlen(str + (*i) + 1));
	str[ft_strlen(str) - 2] = 0;
	(*i)--;
}

void		ft_put_env_0(t_data *d, char *str, int *i)
{
	d->cmd[d->num] = ft_meminsert(str, d->env_tem, *i + 1, *i);
	*i += ft_strlen(d->env_tem) - 1;
}

void		ft_check_env(t_data *d)
{
	int i;
	int j;
	int quote;

	i = -1;
	while (d->cmd[++i])
	{
		j = 0;
		quote = 1;
		while (d->cmd[i][j])
		{
			if (d->cmd[i][j] == '\'' && d->cmd[i][j - 1] != '\\')
				quote *= -1;
			if (d->cmd[i][j] == '$' && quote != -1 && d->cmd[i][j + 1] != '='
				&& d->cmd[i][j + 1] != '\"' && d->cmd[i][j + 1] != '\''
				&& d->cmd[i][j + 1] != ' ' && d->cmd[i][j - 1] != '\\')
			{
				d->num = i;
				ft_put_env(d, d->cmd[i], &j);
			}
			else
				ft_check_env_rs(d->cmd[i], &j);
		}
	}
}
