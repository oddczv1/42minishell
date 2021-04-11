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

	/*
	if (str[*i] == '\\' && str[*i + 1] != '\\' )
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
	*/

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
		ft_memmove(str + i + 1, str + i, ft_strlen(str + i));
		str[i] = '|';
		i++;
		while(str[i] && !ft_isspace(str[i]))
			ft_check_word(str, &i);

	}		
}

void		ft_put_env_value(t_data *d, char *str, int *end, int start, int num)
{
	int i;

	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], str + start, *end - start) && d->env[i][*end - start] == '=')
			d->cmd[num] = ft_meminsert(str, d->env[i] + *end - start + 1, *end, start);
	}
	ft_memmove(str + start - 1, str + *end + 1, ft_strlen(str + *end + 1));
	str[start + ft_strlen(str + *end + 1) - 1] = 0;
}

void		ft_put_env(t_data *d, char *str, int *i, int num)
{
	int start;

	(*i)++;
	if (str[*i] != '{')
	{
		start = *i;
		while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '\"')
			(*i)++;
		ft_put_env_value(d, str, i, start, num);
	}	
	else if (str[*i] == '{')
	{
		start = *i;
		ft_check_braceparam(str, i);
		ft_put_env_value(d, str + 1, i, start, num); //here!!
	}
}

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
				ft_put_env(d, d->cmd[i], &j, i);
			else
				j++;
		}
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
			d->cmd = ft_split_pipe(d->argv[j]);
			ft_check_env(d);
			
			int k = 0;
			while (d->cmd[k])
			{
				printf("%s\n", d->cmd[k]);
				d->cmd[k] = 0;
				k++;
			}
					
			// 역슬러시 없애고
			// 따운표를뺴주고
			//ft_check_redirection(d);
			//ft_command(d);
			//ft_free();			
        }
		//ft_free();
    }
	//ft_free();
}