/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:40:55 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/09 12:06:05 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
#define MAX 50

int main(void)
{
	int len;
	char buf[MAX];
	pid_t pid;
	int status;
	char * argv_list[] = {"/bin/ls", "-al", "-a", NULL};

	ft_putstr_fd(">>>~% ", 1);	
	while (1)
	{
		len = read(0, buf, MAX - 1);
		buf[len] = 0;	
		if (ft_strncmp(buf, "pwd", 3) == 0)
		{
			pid = fork();
			if (pid > 0)
			{
				waitpid(pid,&status, 0);
			}
			else if (pid == 0)
			{
				execv("/bin/ls",argv_list);
				exit(0);
			}
			else
			{
				perror("fork Fail! \n");
				return -1;
			}
		}
		ft_putstr_fd(">>>~% ", 1);
	}
}
*/

static void	init_data(t_data *d, char **argv, char **env)
{
	d->argv = argv;
	d->ret = 0;
	d->str = 0;
	(void)env;
	//*d->env = ft_env(envp, 0);
	d->export = (char **)malloc(sizeof(char *) + 1);
}

int			main(int argc, char **argv, char **env)
{
	t_data	d;
	char	buf[2];

	if (argc != 1)
		return (1);
	init_data(&d, argv, env);
	while (1)
	{
		write(1, ">>> ~% ", 7);
		while ((read(0, buf, 1)) && buf[0]!= '\n' )
			ft_read_str(&d, buf);
		//parse(&d);
	}
	return (0);
}
