/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:45:09 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/15 14:44:38 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_check_split(t_data *d, int idx)
{
	ft_check_argv(d->argv[idx]);
	d->cmd = ft_split_pipe(d->argv[idx]);//편의를 위해 여기서도 그냥 ft_split_pipe쓴것 그냥 스페이스로 나눈다고 생각하면됨.
	ft_check_env(d);
	ft_remove_mark(d);							
	ft_check_redirection(d);
}

void		ft_check_redirection(t_data *d)
{
	int i;

	i = -1;
	while (d->cmd[++i])
	{
		if (ft_memcmp(d->cmd[i], "<", 2) == 0)
		{
			d->fd[0] = open(d->cmd[i + 1], O_RDONLY);
			if (d->fd[0] < 0)
				ft_putstr_fd("err\n", 2);
			d->cmd[i] = 0;	
			break;
		}	
		else if (ft_memcmp(d->cmd[i], ">", 2) == 0)
		{
			d->fd[0] = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			d->fd[1] = dup(1);
			dup2(d->fd[0], 1);
			d->cmd[i] = 0;
			break;
		}	
		else if (ft_memcmp(d->cmd[i], ">>", 3) == 0)
		{
			d->fd[0] = open(d->cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			d->fd[1] = dup(1);
			dup2(d->fd[0], 1);
			d->cmd[i] = 0;
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
	int status;
	pid_t pid;
    int i;
	int j;
	
	i = -1;
	pid = 0;
	d->ft_std[0] = dup(0);
	d->ft_std[1] = dup(1);
	d->cmds = ft_split_semi(d->str);
	if (!d->cmds)
		return ;
	while (d->cmds[++i])
	{
		ft_check_pipe(d->cmds[i]);
		d->argv = ft_split_pipe(d->cmds[i]);
		if (d->argv[1] != NULL)
		{
			if ((pid = fork()) == 0)
				process_pipe(d);//여기안에선 recover_std()함수호출 필요없을듯..? 독립이니까..
			else
			{
				waitpid(pid, &status, 0);
				ft_free(d->argv);
				//recover_std(d);//혹시나해서 넣어두긴하는데 필요없을듯
			}
		}
		else
		{
			j = -1;
			while (d->argv[++j])//반복문을 쓸 필요가 없는데...?
			{
				ft_check_split(d, j);			
				process(d);
				ft_free(d->cmd);			
        	}
			ft_free(d->argv);
    	}
	}
	ft_free(d->cmds);
	return ;
}
