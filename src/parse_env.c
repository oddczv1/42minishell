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

char		**ft_get_env(char **env)
{
	char	**dest;
	int		i;
	int		len;

	len = 0;
	while (env[len])
		len++;
	dest = (char **)malloc((len + 1) * sizeof(char *));
	if (!dest)
		return (0);
	i = -1;
	while (++i < len)
		dest[i] = ft_strdup(env[i]);
	dest[len] = NULL;
	return (dest);
}

void		ft_put_env_value_1(t_data *d, char *str, int *end, int start)
{
	int i;

	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], str + start, *end - start)
				&& d->env[i][*end - start] == '=')
		{
			d->cmd[d->num] =
				ft_meminsert(str, d->env[i] + *end - start + 1, *end, start);
			*end = start - 1 + ft_strlen(d->env[i] + *end - start + 1);
			return ;
		}
	}
	ft_memmove(str + start - 1, str + *end, ft_strlen(str + *end));
	str[start - 1 + ft_strlen(str + *end)] = 0;
	*end = start - 1;
	return ;
}

void		ft_put_env_value_2(t_data *d, char *str, int *end, int start)
{
	int i;

	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], str + start, *end - start)
				&& d->env[i][*end - start] == '=')
		{
			d->cmd[d->num] = ft_meminsert(str,
							d->env[i] + *end - start + 1, *end + 1, start - 1);
			*end = start - 2 + ft_strlen(d->env[i] + *end - start + 1);
			return ;
		}
	}
	ft_memmove(str + start - 2, str + *end + 1, ft_strlen(str + *end + 1));
	str[start - 3 + ft_strlen(str + *end)] = 0;
	*end = start - 2;
	return ;
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

void		ft_put_env(t_data *d, char *str, int *i)
{
	(*i)++;
	d->env_tem = ft_itoa(g_t.status);
	if (str[*i] == '?' && (str[(*i) + 1] == '\0'
		|| str[(*i) + 1] == '\"' || str[(*i) + 1] == '$'))
	{
		d->cmd[d->num] = ft_meminsert(str, d->env_tem, *i + 1, *i);
		*i += ft_strlen(d->env_tem) - 1;
	}
	else if (str[*i] == '{' && str[(*i) + 1] == '?' && str[(*i) + 2] == '}')
	{
		d->cmd[d->num] = ft_meminsert(str, d->env_tem, *i + 3, *i);
		*i += ft_strlen(d->env_tem) - 1;
	}
	else if (str[*i] != '{')
	{
		d->env_start = *i;
		while (str[*i] != ' ' && str[*i] != '\0'
				&& str[*i] != '\"' && str[*i] != '$')
			(*i)++;
		ft_put_env_value_1(d, str, i, d->env_start);
	}
	else if (str[*i] == '{')
		ft_put_env_2(d, str, i);
	free(d->env_tem);
}
