/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:56:36 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/09 11:53:55 by youngrch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
<<<<<<< HEAD
# define huchoi 111
=======
# include <unistd.h>

>>>>>>> 90537e2cc972ad62478fbf2d347df6fa331e33a5
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

typedef struct		s_data{
	int		argc;
	char	**argv;//split by semiclone
	char	**cmd;//if call the func, output is stored this variable.

	char	**envp;
	char	**export;
	int		ret;
	char	*str;
	char	**cmds;
}					t_data;

int		ft_read_str(t_data *d, char *buf);

#endif
