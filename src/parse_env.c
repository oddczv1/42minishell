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

void		ft_put_env_value_1(t_data *d, char *str, int *end, int start)
{
	int i;

	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], str + start, *end - start) && d->env[i][*end - start] == '=')
		{
			d->cmd[d->num] = ft_meminsert(str, d->env[i] + *end - start + 1, *end, start);
			*end = start -1 + ft_strlen(d->env[i] + *end - start + 1);
			return ;
		}						
	}
	ft_memmove(str + start - 1, str + *end, ft_strlen(str + *end));
	str[start -1 + ft_strlen(str + *end)] = 0;
	*end = start -1;
	return ;
}

void		ft_put_env_value_2(t_data *d, char *str, int *end, int start)
{
	int i;

	i = -1;
	while (d->env[++i])
	{							
		if (!ft_strncmp(d->env[i], str + start, *end - start) && d->env[i][*end - start] == '=')
		{
			d->cmd[d->num] = ft_meminsert(str, d->env[i] + *end - start + 1, *end + 1, start - 1);
			*end = start -2 + ft_strlen(d->env[i] + *end - start + 1);
			return ;
		}				
	}
	ft_memmove(str + start - 2, str + *end + 1, ft_strlen(str + *end + 1));
	str[start - 3 + ft_strlen(str + *end)] = 0;
	*end = start - 2;
	return ;
}

void		ft_put_env(t_data *d, char *str, int *i)
{
	int start;

	(*i)++;
	if (str[*i] != '{')
	{
		start = *i;
		while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '\"' && str[*i] != '$' )
			(*i)++;
		ft_put_env_value_1(d, str, i, start);
	}
	else if (str[*i] == '{')
	{
		(*i)++;
		start = *i;
		while (str[*i] && !(str[(*i) - 1] != '\\' && str[*i] == '}'))
			(*i)++;
		if (!str[*i])
		{
			ft_putstr_fd("Non finished braceparam\n", 2);
			d->status = 1;
		}
		else
			ft_put_env_value_2(d, str, i, start);
	}
}
