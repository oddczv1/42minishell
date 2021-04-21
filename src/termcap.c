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

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	ft_insert_char(t_data *d)
{
	char *dest;

	dest = (char *)malloc((g_t.max + 1) * sizeof(char));
	ft_memmove(dest, d->str, g_t.col);
	dest[g_t.col - 1] = (char)g_t.c;
	ft_memmove(dest + g_t.col, d->str + g_t.col - 1, g_t.max - g_t.col);
	dest[g_t.max] = 0;
	free(d->str);
	d->str = dest;
}

void	ft_backspace_char(t_data *d)
{
	char *dest;

	dest = (char *)malloc((g_t.max + 1) * sizeof(char));
	ft_memmove(dest, d->str, g_t.col);
	ft_memmove(dest + g_t.col, d->str + g_t.col + 1, g_t.max - g_t.col);
	dest[g_t.max] = 0;
	free(d->str);
	d->str = dest;
}

int		ft_history_len(void)
{
	int len;

	len = 0;
	while (g_t.history[len])
		len++;
	return (len);
}

int		ft_read_term(t_data *d)
{
	if (g_t.c == 4479771)
		ft_term_left();
	else if (g_t.c == 4414235)
		ft_term_right();
	else if (g_t.c == 127)
		ft_term_backspace(d);
	else if (g_t.c == 2117294875)
		ft_term_delete(d);
	else if (g_t.c == 4283163)
		ft_term_up(d);
	else if (g_t.c == 4348699)
		ft_term_down_1(d);
	else if (g_t.c == 10)
	{
		ft_term_enter(d);
		return (1);
	}
	else if (g_t.c == 4)
		ft_term_d(d);
	else
		ft_term_write(d);
	tputs(tgetstr("ei", NULL), 1, putchar_tc);
	g_t.c = 0;
	return (0);
}
