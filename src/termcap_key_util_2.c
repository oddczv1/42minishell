/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:47:50 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/17 20:48:18 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_term_enter(t_data *d)
{
	write(1, "\n", 1);
	if (d->str != 0 && d->str[0] != 0)
	{
		if (g_t.history[g_t.index] != 0)
			free(g_t.history[g_t.index]);
		g_t.history[g_t.index] = ft_strdup(d->str);
		++g_t.index;
		if (g_t.index == 100)
			g_t.index = 0;
	}
}

void	ft_term_up(t_data *d)
{
	if (g_t.down == 1 && g_t.num > 0)
	{
		--g_t.temindex;
		g_t.down = 0;
	}
	if (g_t.history[g_t.temindex] != 0 && g_t.num > 0)
	{
		while (g_t.col)
		{
			--g_t.col;
			tputs(tgetstr("le", NULL), 1, putchar_tc);
		}
		tputs(tgetstr("ce", NULL), 1, putchar_tc);
		g_t.col = 0;
		g_t.max = 0;
		g_t.col += ft_strlen(g_t.history[g_t.temindex]);
		g_t.max += ft_strlen(g_t.history[g_t.temindex]);
		tputs(g_t.history[g_t.temindex], 1, putchar_tc);
		if (d->str != 0)
			free(d->str);
		d->str = ft_strdup(g_t.history[g_t.temindex]);
		--g_t.temindex;
		--g_t.num;
		g_t.up = 1;
	}
}

void	ft_term_down_1(t_data *d)
{
	if (g_t.up == 1 && g_t.num < ft_history_len())
		++g_t.temindex;
	if (g_t.up == 1 && g_t.num < ft_history_len())
		g_t.up = 0;
	if (g_t.history[g_t.temindex + 1] != 0 && g_t.num < ft_history_len() - 1)
		ft_term_down_2(d);
	else if (g_t.num == ft_history_len() - 1)
	{
		while (g_t.col)
		{
			--g_t.col;
			tputs(tgetstr("le", NULL), 1, putchar_tc);
		}
		tputs(tgetstr("ce", NULL), 1, putchar_tc);
		g_t.col = 0;
		g_t.max = 0;
		g_t.down = 0;
		if (d->str != 0)
			free(d->str);
		d->str = 0;
		++g_t.num;
	}
}

void	ft_term_down_2(t_data *d)
{
	while (g_t.col)
	{
		--g_t.col;
		tputs(tgetstr("le", NULL), 1, putchar_tc);
	}
	tputs(tgetstr("ce", NULL), 1, putchar_tc);
	++g_t.temindex;
	++g_t.num;
	g_t.col = 0;
	g_t.max = 0;
	g_t.col += ft_strlen(g_t.history[g_t.temindex]);
	g_t.max += ft_strlen(g_t.history[g_t.temindex]);
	tputs(g_t.history[g_t.temindex], 1, putchar_tc);
	if (d->str != 0)
		free(d->str);
	d->str = ft_strdup(g_t.history[g_t.temindex]);
	g_t.down = 1;
}

void	ft_term_d(t_data *d)
{
	if (d->str == 0 || d->str[0] == 0)
	{
		tputs("exit\n", 1, putchar_tc);
		g_t.d_flag = 1;
		exit(g_t.status);
	}
}
