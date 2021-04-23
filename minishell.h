/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:56:36 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/22 14:58:53 by huchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>


# define TRUE 1
# define FALSE 0

typedef struct		s_path_var{
	int flag;
	int idx;
	char temp_dir[300];
	char str[300];
	char *temp_file;
	char *p;
}					t_path_var;

typedef struct		s_data{
	int				argc;
	char			**cmds;//if call the func, output is stored this variable.
	char			**argv;//split by semiclone
	char			**cmd;
	char			**env;
	char			**paths;
	char			exec_dir[300];//지우면 안됨 필요함.
	char			exec_file[300];//이건 무조건 필요함.
	char			*str;
	int				fd[2];
	int				ft_std[2];
	int				num;
	int				status;//init할때 얘도 0으로 초기화시켜야함.
	pid_t			*pids;
	int				enable;
	int				flag;
	int				p_i;
	int				p_j;
	int				p_nb;
}					t_data;

typedef struct		s_termcap{
	int				c;
	struct termios	termi;
	struct termios	new_termi;
	int				col;
	int				max;
	char			buf[2];
	char			**history;
	int				num;
	int				index;
	int				temindex;
	int				len;
	int				up;
	int				down;
	pid_t			pids;
	int				status;
	int				d_flag;
}					t_termcap;

t_termcap			g_t;

int					ft_read_str(t_data *d, char *buf);
char				**ft_get_env(char **env);
void				ft_free(char **array);
int					ft_isquote(char *str);
void				ft_check_upper(t_data *d);
void				parse(t_data *d);
void				process(t_data *d);
void				ft_check_redirection(t_data *d);
void				ft_check_upper(t_data *d);
void				ft_check_quote(t_data *d, char *str, int *i, int j);
void				ft_check_redirection_one(char *str, int *i);
void				ft_check_redirection_two(char *str, int *i);
void				ft_remove_mark(t_data *d);
void				ft_check_redirection(t_data *d);
void				ft_check_env(t_data *d);
int     			ft_check_escape_num(char *str, int i);
void				ft_check_word(t_data *d, char *str, int *i);
void				ft_check_argv(t_data *d, char *str);
void				ft_check_pipe(t_data *d, char *str);

void				ft_command(t_data *d, int *fd_std, int *fd_cmd, int pipe1);
void				ft_put_env_value(t_data *d, char *str,
								int *end, int start, int brac);
void				ft_put_env(t_data *d, char *str, int *i);

void				is_pipe(t_data *d);
void				non_pipe(t_data *d);

void				delete_last_newline(char **cmd);
int					match_key(char *key_value, char *str);
void				get_value(char *str, char *buf);
int					findenv(t_data *data, char *buf);
void				renewer_env(t_data *data, char *key, char *str, int size);
int					delete_env(t_data *data, char *key);
int					add_env(t_data *data, char *key_value);
int					is_newline(char *str);
void				my_putstr_fd(char *str, int fd);
void				process_pipe(t_data *d);
int					pipe_func(t_data *data, int *fx, int fd, int idx);

int					ft_read_term(t_data *d);
int					putchar_tc(int tc);
void				ft_insert_char(t_data *d);
void				ft_backspace_char(t_data *d);
int					ft_history_len(void);
void				ft_term_left(void);
void				ft_term_right(void);
void				ft_term_backspace(t_data *d);
void				ft_term_delete(t_data *d);
void				ft_term_write(t_data *d);
void				ft_term_enter(t_data *d);
void				ft_term_up(t_data *d);
void				ft_term_down_1(t_data *d);
void				ft_term_down_2(t_data *d);
void				ft_term_d(t_data *d);

void				porcess_echo(t_data *data);
void				recover_std(t_data *d);
void				process_pwd(t_data *data);
void				process_env(t_data *data);
void				process_cd(t_data *data);
void				process_export(t_data *data);
void				process_unset(t_data *data);
void				process_bash(t_data *data);
int					is_exec_usr(t_data *data);
int					is_exec_bin(t_data *data);
int					is_builtin(t_data *data);
int					get_exec_dir_file(t_data *data);
void				process_builtin(t_data *data);
void				ft_check_split(t_data *d, int idx);
void				get_paths(t_data *data);
int     			execfile_in_path(t_data *data, char *path);
void				over_write(t_data *data, char *key_value, int idx);
void				signal_handler(int signum);
int					is_valid(char *str);
#endif
