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

void		ft_free(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}


void		ft_check_redirection(t_data *d)
{
	int i;

	i = -1;
	while (d->cmd[++i])
	{
		if (ft_memcmp(d->cmd[i], "<", 2) == 0)
		{
			d->fd = open(d->cmd[i + 1], O_RDONLY);
			if (d->fd < 0)
				ft_putstr_fd("err\n", 2);  //read err
			char buffer[20];
			int read_size;
			//dup2(d->fd, 0);
			while ((read_size = read(d->fd, buffer, 20)) > 0)
				buffer[read_size] = 0;
			ft_putstr_fd(buffer, 1);
			close(d->fd);
			break;
		}	
		else if (ft_memcmp(d->cmd[i], ">", 2) == 0)
		{
			d->fd = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			char buffer[20] = "1111\n";
			//dup2(d->fd, 1);
			write(d->fd,  buffer, strlen(buffer));
			close(d->fd);
			break;
		}	
		else if (ft_memcmp(d->cmd[i], ">>", 3) == 0)
		{
			d->fd = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			char buffer[20] = "2222\n";
			//dup2(d->fd, 1);
			write(d->fd,  buffer, strlen(buffer));
			close(d->fd);
			break;
		}	
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
			{
				d->num = i;
				ft_put_env(d, d->cmd[i], &j);
			}
			else
				j++;
		}
	}		
}


void		ft_check_word(char *str, int *i)
{
	if ((str[(*i) - 1] != '\\' && str[*i] == '\'') || 
		(str[(*i) - 2] == '\\' && str[(*i) - 1] == '\\' && str[*i] == '\''))
		ft_check_quote(str, i, 1);
	else if ((str[(*i) - 1] != '\\' && str[*i] == '\"') || 
		(str[(*i) - 2] == '\\' && str[(*i) - 1] == '\\' && str[*i] == '\"'))
		ft_check_quote(str, i, 2);
	else if (str[(*i) - 1] != '\\' && str[*i] == '>' && str[*i + 1] != '>')
		ft_check_redirection_one(str, i);
	else if (str[(*i) - 1] != '\\' && str[*i] == '<' && str[*i + 1] != '<')
		ft_check_redirection_one(str, i);
	else if (str[(*i) - 1] != '\\' && str[*i] == '>' && str[*i + 1] == '>')
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
		{
			str[i] = '|';
			i++;
		}
		if (str[i] == '\0')
			break ;
		while(str[i] && !ft_isspace(str[i]))
			ft_check_word(str, &i);

	}		
}

void        parse(t_data *d)
{
    int i;
	int j;

	i = -1;
	d->cmds = ft_split_semi(d->str);
	if (!d->cmds)
		return ;
	while (d->cmds[++i])
	{
		d->argv = ft_split_pipe(d->cmds[i]);
		j = -1;
		while (d->argv[++j])
		{
			ft_check_argv(d->argv[j]);
			d->cmd = ft_split_pipe(d->argv[j]);
			ft_check_env(d);
			ft_remove_mark(d);							
			ft_check_redirection(d);
			//ft_command(d);
			ft_free(d->cmd);			
        }
		ft_free(d->argv);
    }
	ft_free(d->cmds);
	return ;
}