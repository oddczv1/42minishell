/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:45:09 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/09 23:45:12 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void		ft_check_word(char *str, int *i)
{
	if (str[(*i) - 1] != '\\' && str[*i] == '\'')
		ft_check_quote(str, i, 1);
	else if (str[(*i) - 1] != '\\' && str[*i] == '\"')
		ft_check_quote(str, i, 2);
	else if (str[(*i) - 1] != '\\' && str[*i] == '>' && str[*i + 1] != '>')
		ft_check_redirection_one(str, i);
	else if (str[(*i) - 1] != '\\' && str[*i] == '<' && str[*i + 1] != '<')
		ft_check_redirection_one(str, i);
	else if (str[(*i) - 1] != '\\' && str[*i] == '>' && str[*i + 1] == '>')
		ft_check_redirection_two(str, i);
	else if (str[(*i) - 1] != '\\' && str[*i] == '<' && str[*i + 1] == '<')
		ft_check_redirection_two(str, i);
	else if (str[*i] == '\\' && str[*i + 1] != '\\' )
	{
		ft_memmove(str + *i , str + *i + 1, ft_strlen(str + *i + 1));
		str[ft_strlen(str) - 1] = 0;
	}
	else if (str[*i] == '\\' && str[*i + 1] == '\\' )
	{
		ft_memmove(str + *i , str + *i + 1, ft_strlen(str + *i + 1));
		str[ft_strlen(str) - 1] = 0;
		(*i)++;
	}
	else
		(*i)++;
}

void		ft_check_argv(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		while(str[i] && !ft_isspace(str[i]))
			ft_check_word(str, &i);
	}		
}

void		ft_check_env(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
	//	if (str[i] == '$' && ( || ))
	//		printf("asd\n");
		i++;
	}		
}

void        parse(t_data *d)
{
    int i;
    int j;

	i = -1;
	d->cmds = ft_split_semi(d->str);
	while (d->cmds[++i])
	{
		d->argv = ft_split_pipe(d->cmds[i]);
		j = -1;
		while (d->argv[++j])
		{
			ft_check_argv(d->argv[j]);
			ft_check_env(d->argv[j]);
			printf("%s\n", d->argv[j]);
			//d->cmd = ft_split_space(d->argv[j]);
			//ft_check_redirection(d);
			//ft_free();			
        }
		//ft_free();
    }
	//ft_free();
}