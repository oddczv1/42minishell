/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mark.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:01:24 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/10 20:02:10 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_remove_mark(t_data *d)
{
	int i;
	
	i = -1;
	while (d->cmd[++i])
	{
		ft_removechar(d->cmd[i], '\\');
	}	

	i = -1;
	while (d->cmd[++i])
	{
		ft_removechar(d->cmd[i], '\'');
		ft_removechar(d->cmd[i], '\"');
	}		
}

void		ft_check_pipe(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[(i) - 1] != '\\' && str[i] == '|')
		{
			(i)++;
			while (ft_isspace(str[i]))
				(i)++;
			if(!str[i])
				ft_putstr_fd("pipe error\n", 2);
		}
		else
			(i)++;
	}
}

void		ft_check_quote(char *str, int *i, int d)
{
	if (d == 1)
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (!str[*i])
			ft_putstr_fd("Non finished quote\n", 2);
		else
			(*i)++;
	}
	else if (d == 2)
	{
		(*i)++;
		while (str[*i] && !((str[(*i) - 1] != '\\' && str[*i] == '\"') || 
		(str[(*i) - 2] == '\\' && str[(*i) - 1] == '\\' && str[*i] == '\"')))
			(*i)++;
		if (!str[*i])
			ft_putstr_fd("Non finished dquote\n", 2);
		else
			(*i)++;
	}

}

void		ft_check_redirection_one(char *str, int *i)
{
	if (!ft_isspace(str[(*i) - 1]) && ft_isspace(str[(*i) + 1]))
	{
		ft_memmove(str + *i + 1, str + *i, ft_strlen(str + *i));
		str[*i] = '|';
		*i += 2;
	}
	else if (ft_isspace(str[(*i) - 1]) && !ft_isspace(str[(*i) + 1]))
	{
		ft_memmove(str + *i + 2, str + *i + 1, ft_strlen(str + *i + 1));
		str[*i + 1] = '|';
		*i += 2;
	}
	else if (!ft_isspace(str[(*i) - 1]) && !ft_isspace(str[(*i) + 1]))
	{
		ft_memmove(str + *i + 1, str + *i, ft_strlen(str + *i));
		str[*i] = '|';
		ft_memmove(str + *i + 2, str + *i + 1, ft_strlen(str + *i + 1));
		str[*i + 2] = '|';
		*i += 3;
	}		
}

void		ft_check_redirection_two(char *str, int *i)
{
	if (!ft_isspace(str[(*i) - 1]) && ft_isspace(str[(*i) + 2]))
	{
		ft_memmove(str + *i + 1, str + *i, ft_strlen(str + *i));
		str[*i] = '|';
		*i += 3;
	}
	else if (ft_isspace(str[(*i) - 1]) && !ft_isspace(str[(*i) + 2]))
	{
		ft_memmove(str + *i + 3, str + *i + 2, ft_strlen(str + *i + 2));
		str[*i + 2] = '|';
		*i += 3;
	}
	else if (!ft_isspace(str[(*i) - 1]) && !ft_isspace(str[(*i) + 2]))
	{
		ft_memmove(str + *i + 1, str + *i, ft_strlen(str + *i));
		str[*i] = '|';
		ft_memmove(str + *i + 3, str + *i + 2, ft_strlen(str + *i + 2));
		str[*i + 3] = '|';
		*i += 4;
	}
}
