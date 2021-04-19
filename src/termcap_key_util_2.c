/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+        */
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
		if (t.history[t.index] != 0)
			free(t.history[t.index]);
		t.history[t.index] = ft_strdup(d->str);
		++t.index;
		if (t.index == 100)
			t.index = 0;
	}
}

void	ft_term_up(t_data *d)
{
	if (t.down == 1 && t.num > 0)
	{
		--t.temindex;
		t.down = 0;
	}
	if (t.history[t.temindex] != 0 && t.num > 0)
	{
		while (t.col)
		{
			--t.col;
			tputs(tgetstr("le", NULL), 1, putchar_tc);	
		}
		tputs(tgetstr("ce", NULL), 1, putchar_tc);
		t.col = 0;
		t.max = 0;
		t.col += ft_strlen(t.history[t.temindex]);
		t.max += ft_strlen(t.history[t.temindex]);
		tputs(t.history[t.temindex], 1, putchar_tc);
		if (d->str !=0)
			free(d->str);
		d->str = ft_strdup(t.history[t.temindex]);
		--t.temindex;
		--t.num;
		t.up = 1;
	}
}

void	ft_term_down_1(t_data *d)
{	
	if (t.up == 1 && t.num < ft_history_len())
			++t.temindex;
	if (t.up == 1 && t.num < ft_history_len())
			t.up = 0;
	if (t.history[t.temindex + 1] != 0 && t.num < ft_history_len() -1)
	{
		while (t.col)
		{
			--t.col;
			tputs(tgetstr("le", NULL), 1, putchar_tc);	
		}
		tputs(tgetstr("ce", NULL), 1, putchar_tc);
		++t.temindex;
		++t.num;
		t.col = 0;
		t.max = 0;
		t.col += ft_strlen(t.history[t.temindex]);
		t.max += ft_strlen(t.history[t.temindex]);
		tputs(t.history[t.temindex], 1, putchar_tc);
		if (d->str !=0)
			free(d->str);
		d->str = ft_strdup(t.history[t.temindex]);
		t.down = 1;
	}
	else if (t.num == ft_history_len() - 1)
		ft_term_down_2(d);
}

void	ft_term_down_2(t_data *d)
{
		while (t.col)
		{
			--t.col;
			tputs(tgetstr("le", NULL), 1, putchar_tc);	
		}
		tputs(tgetstr("ce", NULL), 1, putchar_tc);
		t.col = 0;
		t.max = 0;
		t.down = 0;
		if (d->str != 0)
			free(d->str);
		d->str = 0;
		++t.num;
}
