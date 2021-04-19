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
	d->ret = 0;
	d->str = 0;
	d->fd[0] = 0;
	d->num = 0;
	d->env = ft_get_env(env);
	d->export = (char **)malloc(sizeof(char *) * 2);
	tcgetattr(0, &t.termi);
	t.buf[1] = 0;
	t.index = 0;
	t.history = (char **)malloc(sizeof(char *) * 101);
	ft_memset_array(t.history, 0, 101);
	t.termi.c_lflag &= (~ECHO);//입력을 다시 출력
	t.termi.c_lflag &= (~ICANON);//캐노니컬 입력 모드를 사용
	//t.termi.c_lflag &= (~ISIG); // 특수문자 무시
	t.termi.c_cc[VMIN] = 1;
	t.termi.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &t.termi);
	tgetent(NULL, "xterm");
	get_paths(d);
	d->status = 0;
}

void		init_term()
{
	t.c = 0;
	t.col = 0;
	t.max = 0;
	t.up = 0;
	t.down = 0;
	t.temindex = t.index - 1;
	t.num = ft_history_len();
}

int			main(int argc, char **argv, char **env)
{
	t_data	d;

	if (argc != 1)
		return (1);
	init_data(&d, argv, env);
	while (1)
	{
		write(2, ">>> ~% ", 7);
		init_term();
		while (read(0, &t.c, sizeof(t.c)) > 0)
		{
			if (ft_read_term(&d) == 1)
				break;
		}
		parse(&d);
		free(d.str);
		d.str = 0;
	}
	return (0);
}
