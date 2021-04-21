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

void	ft_term_left()
{
	if (g_t.col > 0)
	{
	       --g_t.col;
		tputs(tgetstr("le", NULL), 1, putchar_tc);				
	}
}

void	ft_term_right()
{
	if (g_t.col < g_t.max)
	{
		++g_t.col;
		tputs(tgetstr("nd", NULL), 1, putchar_tc);
	}		
}

void	ft_term_backspace(t_data *d)
{	
	if (g_t.col > 0)
	{
		--g_t.col;
		--g_t.max;
		tputs(tgetstr("le", NULL), 1, putchar_tc);
		tputs(tgetstr("dc", NULL), 1, putchar_tc);
		ft_backspace_char(d);
	}
}

void	ft_term_delete(t_data *d)
{
	if (g_t.max > g_t.col && g_t.col >= 0)
	{
		--g_t.max;
	    tputs(tgetstr("dc", NULL), 1, putchar_tc);
		ft_backspace_char(d);			
	}
}

void	ft_term_write(t_data *d)
{ 
	++g_t.col;
	++g_t.max;
	tputs(tgetstr("im", NULL), 1, putchar_tc);
	write(0, &g_t.c, 1);
	g_t.buf[0] = (char)g_t.c;
	if (g_t.col == g_t.max)
		ft_read_str(d, g_t.buf);
	else
    	ft_insert_char(d);
}
