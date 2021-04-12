/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:12:40 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/12 22:14:44 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_put_env_value(t_data *d, char *str, int *end, int start, int brac)
{
	int i;

	i = -1;
	if (brac == 0)
	{
		while (d->env[++i])
		{
			if (!ft_strncmp(d->env[i], str + start, *end - start) && d->env[i][*end - start] == '=')
				d->cmd[d->num] = ft_meminsert(str, d->env[i] + *end - start + 1, *end, start);
		}
		ft_memmove(str + start - 1, str + *end + 1, ft_strlen(str + *end + 1));
		str[start + ft_strlen(str + *end + 1) - 1] = 0;
	}
	else if (brac == 1)
	{
		while (d->env[++i])
		{
							
			if (!ft_strncmp(d->env[i], str + start + 1, *end - start - 1) && d->env[i][*end - start - 1] == '=')
				d->cmd[d->num] = ft_meminsert(str, d->env[i] + *end - start, *end + 1, start);
		}
		ft_memmove(str + start - 1, str + *end, ft_strlen(str + *end));
		str[start -2 + ft_strlen(str + *end)] = 0;
	}

}

void		ft_put_env(t_data *d, char *str, int *i)
{
	int start;

	(*i)++;
	if (str[*i] != '{')
	{
		start = *i;
		while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '\"')
			(*i)++;
		ft_put_env_value(d, str, i, start, 0);
	}	
	else if (str[*i] == '{')
	{
		start = *i;
		ft_check_braceparam(str, i);
		ft_put_env_value(d, str, i, start, 1);
	}
}
