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

void		init_data(t_data *d, char **argv, char **env)
{
	d->argv = argv;
	d->str = 0;
	d->fd[0] = 0;
	d->num = 0;
	d->env = ft_get_env(env);
	t.buf[1] = 0;
	t.index = 0;
	t.history = (char **)malloc(sizeof(char *) * 101);
	ft_memset_array(t.history, 0, 101);
	tcgetattr(0, &t.termi);
	t.new_termi = t.termi;
	t.new_termi.c_lflag &= (~ECHO);
	t.new_termi.c_lflag &= (~ICANON);
	t.new_termi.c_cc[VMIN] = 1;
	t.new_termi.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &t.termi);
	tgetent(NULL, "xterm");
	get_paths(d);
	t.status = 0;
	t.d_flag = 0;
}

void		init_term()
{
	t.c = 0;
	t.col = 0;
	t.max = 0;
	t.up = 0;
	t.down = 0;
	t.pids = 0;
	t.flag = 0;
	t.temindex = t.index - 1;
	t.num = ft_history_len();
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)//ctrl c    개행되면서           /  결과 1    /슬립중시도시   바로종료  / 결과:130 /
	{
		//ft_putstr_fd(ft_itoa(t.pids), 2);
		//

		//int status;
		//kill(t.pids, signum);
		//printf("%d\n", t.pids);
		//signal(signum, SIG_IGN);
		//signal(SIGINT, signal_handler);
		if (!t.pids && t.flag == 0)
		{
			ft_putstr_fd("\n", 2);
			write(2, ">>> ~% ", 7);				
		}
		else
		{		
			ft_putstr_fd("a\n", 2);
		}
	}
	else if (signum == SIGQUIT) //ctrl /   평소에는 아무 실행 안함 /  결과 131  /슬립중시도시   바로종료 ^\Quit: 3
	{
		if (t.pids && t.flag == 0)
		{
			ft_putstr_fd("Quit : 3 \n", 2);
			//write(2, ">>> ~% ", 7);				
		}
	}
}

int			main(int argc, char **argv, char **env)
{
	t_data	d;

	if (argc != 1)
		return (1);
	init_data(&d, argv, env);
	

//  ctrl d   다종료됨             /  결과 0   / 슬립중시도시 슬립끝나고 종료      /  

	while (!t.d_flag)
	{
		write(2, ">>> ~% ", 7);
		//printf("%d\n", t.flag);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		tcsetattr(0, TCSANOW, &t.new_termi);
		init_term();
		while ((read(0, &t.c, sizeof(t.c))) > 0)
		{
			
			if (ft_read_term(&d) == 1)
				break;
		}
		tcsetattr(0, TCSANOW, &t.termi);
		parse(&d);
		free(d.str);
		d.str = 0;
	}
	return (t.status);
}

/*
void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		kill(g_mini->fork, signo);
		g_mini->signal = 1;
		g_mini->ispipe = 0;
		signal(signo, SIG_IGN);
		signal(SIGINT, sig_handler);
		run_touch();
		write(1, "\n", 1);
		print_prompt(1);
	}
	else if (signo == SIGQUIT && g_mini->exec == 1) ctrl / 
	{
		g_mini->ispipe = 0;
		kill(g_mini->fork, signo);
		g_mini->signal = 1;
		signal(signo, SIG_IGN);
		signal(SIGQUIT, sig_handler);
		write(1, "Quit: 3\n", 8);
		print_prompt(1);
	}
}
*/
