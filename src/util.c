/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:33:49 by marvin            #+#    #+#             */
/*   Updated: 2021/04/14 14:06:08 by huchoi           ###   ########.fr       */
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

void		ft_remove_mark(t_data *d)
{
	int i;

	i = -1;
	while (d->cmd[++i])
		ft_removechar(d->cmd[i], '\\');
	i = -1;
	while (d->cmd[++i])
	{
		ft_removechar(d->cmd[i], '\'');
		ft_removechar(d->cmd[i], '\"');
	}
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

void		ft_free(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
