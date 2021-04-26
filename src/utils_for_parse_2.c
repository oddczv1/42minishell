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

void		ft_check_rs_err(char *str, int *i, int num)
{
	g_t.rs_len = num;
	num = num % 2;
	if (num == 1)
	{
		ft_putstr_fd("Non finished Backslash\n", 2);
		g_t.status = 1;
		g_t.err = 1;
	}
	else
	{
		ft_memmove(str + (*i), str + (*i) + g_t.rs_len / 2,
					ft_strlen(str + (*i) + g_t.rs_len / 2));
		str[ft_strlen(str) - g_t.rs_len / 2] = 0;
		(*i) = (*i) + (g_t.rs_len / 2) - 1;
	}
}

void		ft_check_rs(char *str, int *i)
{
	int j;
	int num;

	j = *i;
	num = 1;
	while (str[++j] == '\\')
		++num;
	if (!str[j] && (g_t.idx == g_t.max_idx - 1))
		ft_check_rs_err(str, i, num);
	else
	{
		g_t.rs_len = num - 1;
		ft_memmove(str + (*i), str + (*i) + 1, ft_strlen(str + (*i) + 1));
		str[ft_strlen(str) - 1] = 0;
		if (g_t.rs_len > 0)
		{
			g_t.rs_len = g_t.rs_len / 2;
			ft_memmove(str + (*i), str + (*i) + g_t.rs_len,
						ft_strlen(str + (*i) + g_t.rs_len));
			str[ft_strlen(str) - g_t.rs_len] = 0;
			(*i) = (*i) + num - (g_t.rs_len) - 1;
		}
		if (str[*i] == '\"' || str[*i] == '\'')
			(*i) += 1;
	}
}
