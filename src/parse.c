/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:45:09 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 15:04:12 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_check_env(t_data *d)
{
	int i;
	int j;
	int quote;

	i = -1;
	while (d->cmd[++i])
	{
		j = 0;
		quote = 1;
		while (d->cmd[i][j])
		{
			if (d->cmd[i][j] == '\'' && d->cmd[i][j - 1] != '\\')
				quote *= -1;
			if (d->cmd[i][j] == '$' && quote != -1)
			{
				d->num = i;
				ft_put_env(d, d->cmd[i], &j);
			}
			else
				j++;
		}
	}
}

void		ft_check_word(t_data *d, char *str, int *i)
{
	if ((str[(*i) - 1] != '\\' && str[*i] == '\'') ||
		(str[(*i) - 2] == '\\' && str[(*i) - 1] == '\\' && str[*i] == '\''))
		ft_check_quote(d, str, i, 1);
	else if ((str[(*i) - 1] != '\\' && str[*i] == '\"') ||
		(str[(*i) - 2] == '\\' && str[(*i) - 1] == '\\' && str[*i] == '\"'))
		ft_check_quote(d, str, i, 2);
	else if (str[(*i) - 1] != '\\' && str[*i] == '>' && str[*i + 1] != '>')
		ft_check_redirection_one(str, i);
	else if (str[(*i) - 1] != '\\' && str[*i] == '<' && str[*i + 1] != '<')
		ft_check_redirection_one(str, i);
	else if (str[(*i) - 1] != '\\' && str[*i] == '>' && str[*i + 1] == '>')
		ft_check_redirection_two(str, i);
	else
		(*i)++;
}

void		ft_check_argv(t_data *d, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
		{
			str[i] = '|';
			i++;
		}
		if (str[i] == '\0')
			break ;
		while (str[i] && !ft_isspace(str[i]))
			ft_check_word(d, str, &i);
	}
}

void		ft_check_split(t_data *d, int idx)
{
	d->flag = 0;
	ft_check_argv(d, d->argv[idx]);
	d->cmd = ft_split_pipe(d->argv[idx]);
	ft_check_env(d);
	ft_remove_mark(d);
	ft_check_redirection(d);
	ft_check_upper(d);
}

void		parse(t_data *d)
{
	d->p_i = -1;
	d->enable = 0;
	d->ft_std[0] = dup(0);
	d->ft_std[1] = dup(1);
	d->cmds = ft_split_semi(d->str);
	if (!d->cmds)
		return ;
	while (d->cmds[++d->p_i])
	{
		ft_check_pipe(d, d->cmds[d->p_i]);
		d->argv = ft_split_pipe(d->cmds[d->p_i]);
		if (d->argv[1] != NULL && !d->enable)
			is_pipe(d);
		else
			non_pipe(d);
		ft_free(d->argv);
	}
	ft_free(d->cmds);
	return ;
}
