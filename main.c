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

static void	init_data(t_data *d, char **argv, char **env)
{
	d->argv = argv;
	d->ret = 0;
	d->str = 0;
	d->fd = -1;
	d->num = 0;
	d->env = ft_get_env(env);
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
		parse(&d);
		free(d.str);
		d.str = 0;
	}
	return (0);
}
