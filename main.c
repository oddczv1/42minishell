/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:40:55 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 14:57:55 by huchoi           ###   ########.fr       */
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
	g_t.buf[1] = 0;
	g_t.index = 0;
	g_t.history = (char **)malloc(sizeof(char *) * 101);
	ft_memset_array(g_t.history, 0, 101);
	tcgetattr(0, &g_t.termi);
	g_t.new_termi = g_t.termi;
	g_t.new_termi.c_lflag &= (~ECHO);
	g_t.new_termi.c_lflag &= (~ICANON);
	g_t.new_termi.c_cc[VMIN] = 1;
	g_t.new_termi.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_t.termi);
	tgetent(NULL, "xterm");
	get_paths(d);
	g_t.status = 0;
	g_t.d_flag = 0;
}

void		init_term(void)
{
	g_t.c = 0;
	g_t.col = 0;
	g_t.max = 0;
	g_t.up = 0;
	g_t.down = 0;
	g_t.pids = 0;
	g_t.temindex = g_t.index - 1;
	g_t.num = ft_history_len();
}

void		signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_t.status = 1;
		if (!g_t.pids)
		{
			ft_putstr_fd("\n", 2);
			write(2, ">>> ~% ", 7);
		}
		else
			ft_putstr_fd("\n", 2);
	}
	else if (signum == SIGQUIT)
	{
		if (g_t.pids)
			ft_putstr_fd("Quit : 3 \n", 2);
	}
}

int			main(int argc, char **argv, char **env)
{
	t_data	d;

	if (argc != 1)
		return (1);
	init_data(&d, argv, env);
	while (!g_t.d_flag)
	{
		write(2, ">>> ~% ", 7);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		tcsetattr(0, TCSANOW, &g_t.new_termi);
		init_term();
		while ((read(0, &g_t.c, sizeof(g_t.c))) > 0)
		{
			if (ft_read_term(&d) == 1)
				break ;
		}
		tcsetattr(0, TCSANOW, &g_t.termi);
		parse(&d);
		free(d.str);
		d.str = 0;
	}
	return (g_t.status);
}
