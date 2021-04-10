/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:33:49 by marvin            #+#    #+#             */
/*   Updated: 2020/12/10 15:54:47 by parmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_read_str(t_data *d, char *buf)
{
	char *tem;

	if (!(tem = ft_strjoin(d->str, buf)))
		return (0);
	if (d->str)
		free(d->str);
	d->str = tem;
	return (1);
}

char	**ft_get_env(char **env)
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
	dest[len] = 0;
	return (dest);
}