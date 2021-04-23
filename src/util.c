/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:33:49 by huchoi            #+#    #+#             */
/*   Updated: 2021/04/22 18:59:26 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_remove_mark(t_data *d)
{
	int i;
	int quote;

	i = -1;
	while (d->cmd[++i])
	{
		quote = ft_isquote(d->cmd[i]);
		if (quote == 0 && (!ft_check_escape_num(d->cmd, i) && d->cmd[i] == '\"'))
		{
			ft_removechar(d->cmd[i], '\"');
		}
			
		quote = 0;
	}
		/*
	i = -1;
	while (d->cmd[++i])
	{
		quote = ft_isquote(d->cmd[i]);
		if (quote == 0)
		{
			ft_removechar(d->cmd[i], '\'');
		}
		quote = 0;
	}

	


	i = -1;
	while (d->cmd[++i])
		ft_removechar(d->cmd[i], '\\');
	i = -1;
	while (d->cmd[++i])
		ft_removechar(d->cmd[i], '\"');
	i = -1;
	while (d->cmd[++i])
	{
		quote =  ft_isquote(d->cmd[i]);
		if (quote == 0)
			ft_removechar_2(d->cmd[i], '\\');
		quote = 0;
	}
	i = -1;
	*/

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
