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

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	ft_insert_char(t_data *d)
{
	char *dest;

	dest = (char*)malloc((t.max + 1)*sizeof(char));
	ft_memmove(dest, d->str, t.col);
	dest[t.col - 1] = (char)t.c;
	ft_memmove(dest + t.col, d->str + t.col - 1, t.max - t.col);
	dest[t.max] = 0;
	free(d->str);
	d->str = dest;
}

void	ft_backspace_char(t_data *d)
{
	char *dest;

	dest = (char*)malloc((t.max + 1)*sizeof(char));
	ft_memmove(dest, d->str, t.col);
	ft_memmove(dest + t.col, d->str + t.col + 1, t.max - t.col);
	dest[t.max] = 0;
	free(d->str);
	d->str = dest;
}

int		ft_history_len()
{
	int len;

	len = 0;
	while(t.history[len])
	{
		len++;
	}
	return len;
}

int    ft_read_term(t_data *d)
{
    if (t.c ==  4479771) //left
		ft_term_left();
	else if(t.c ==  4414235)//right
		ft_term_right();
	else if (t.c == 127) //backspace
		ft_term_backspace(d);
	else if (t.c == 2117294875) //delete
		ft_term_delete(d);
	else if (t.c == 4283163)// up
		ft_term_up(d);
	else if (t.c == 4348699) //duwn
		ft_term_down_1(d);
	else if (t.c == 10) // enter
	{
		ft_term_enter(d);
		return (1);
	}
	else if (t.c == 9)
	{
		
	}
	else // write
		ft_term_write(d);
	tputs(tgetstr("ei", NULL), 1, putchar_tc);
	t.c = 0;
    return 0;
}