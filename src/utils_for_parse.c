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

void		ft_remover_rs(char *str, int i)
{
	int back;

	if (g_t.rs_len != 0)
	{
		back = i - g_t.rs_len;
		while (1)
		{
			if ((str[back] == '\\' && str[back + 1] == '\\')
				|| (str[back] == '\\' && str[back + 1] == '\"'))
			{
				ft_memmove(str + back,
							str + back + 1, ft_strlen(str + back + 1));
				str[ft_strlen(str) - 1] = 0;
				back++;
			}
			else
				back++;
			if (back == i - (g_t.rs_len / 2))
				break ;
		}
	}
}

void		ft_removechar_3(char *str, int *i, int *dquote)
{
	if (!ft_check_escape_num(str, *i) && str[*i] == '\"')
	{
		ft_memmove(str + (*i), str + (*i) + 1, ft_strlen(str + (*i) + 1));
		str[ft_strlen(str) - 1] = 0;
		ft_remover_rs(str, *i);
		(*i) = (*i) - (g_t.rs_len / 2);
		(*dquote) *= -1;
	}
	else if (ft_check_escape_num(str, *i) && str[*i] == '\"')
	{
		ft_remover_rs(str, *i);
		(*i) = (*i) - (g_t.rs_len / 2);
	}
	else if (str[(*i) - 1] == '\\' && str[*i] != '\\')
	{
		ft_check_escape_num(str, *i);
		ft_remover_rs(str, *i);
		(*i) = (*i) - (g_t.rs_len / 2) + 1;
	}
	else
		(*i)++;
}

void		ft_removechar_2(char *str, int *i, int *quote, int *dquote)
{
	if (!ft_check_escape_num(str, *i) && str[*i] == '\'')
	{
		ft_memmove(str + (*i), str + (*i) + 1, ft_strlen(str + (*i) + 1));
		str[ft_strlen(str) - 1] = 0;
		ft_remover_rs(str, *i);
		(*i) = (*i) - (g_t.rs_len / 2);
		*quote *= -1;
	}
	else if (!ft_check_escape_num(str, *i) && str[*i] == '\"')
	{
		ft_memmove(str + (*i), str + (*i) + 1, ft_strlen(str + (*i) + 1));
		str[ft_strlen(str) - 1] = 0;
		ft_remover_rs(str, *i);
		(*i) = (*i) - (g_t.rs_len / 2);
		(*dquote) *= -1;
	}
	else
		(*i)++;
}

void		ft_removechar(char *str)
{
	int i;
	int quote;
	int dquote;

	i = 0;
	quote = 1;
	dquote = 1;
	while (str[i])
	{
		if (quote == 1 && dquote == 1)
			ft_removechar_2(str, &i, &quote, &dquote);
		else if (quote == 1 && dquote == -1)
			ft_removechar_3(str, &i, &dquote);
		else if (quote == -1 && dquote == 1)
		{
			if (str[i] == '\'')
			{
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1));
				str[ft_strlen(str) - 1] = 0;
				quote *= -1;
			}
			else
				++i;
		}
	}
}

void		ft_remove_mark(t_data *d)
{
	int i;

	i = -1;
	while (d->cmd[++i])
		ft_removechar(d->cmd[i]);
}
