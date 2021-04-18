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
	if (t.col > 0)
	{
	       --t.col;
		tputs(tgetstr("le", NULL), 1, putchar_tc);				
	}
}

void	ft_term_right()
{
	if (t.col < t.max)
	{
		++t.col;
		tputs(tgetstr("nd", NULL), 1, putchar_tc);
	}		
}

void	ft_term_backspace(t_data *d)
{	
	if (t.col > 0)
	{
		--t.col;
		--t.max;
		tputs(tgetstr("le", NULL), 1, putchar_tc);
		tputs(tgetstr("dc", NULL), 1, putchar_tc);
		ft_backspace_char(d);
	}
}

void	ft_term_delete(t_data *d)
{
	if (t.max > t.col && t.col >= 0)
	{
		--t.max;
	    tputs(tgetstr("dc", NULL), 1, putchar_tc);
		ft_backspace_char(d);			
	}
}

void	ft_term_write(t_data *d)
{ 
	++t.col;
	++t.max;
	tputs(tgetstr("im", NULL), 1, putchar_tc);
	write(0, &t.c, 1);
	t.buf[0] = (char)t.c;
	if (t.col == t.max)
		ft_read_str(d, t.buf);
	else
    	ft_insert_char(d);
}
