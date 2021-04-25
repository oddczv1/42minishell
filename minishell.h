/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:56:36 by youngrch          #+#    #+#             */
/*   Updated: 2021/04/25 17:00:43 by huchoi           ###   ########.fr       */
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
	int				flag;
	int				idx;
	char			temp_dir[300];
	char			str[300];
	char			*temp_file;
	char			*p;
}					t_path_var;

typedef struct		s_data{
	int				argc;
	char			**cmds;
	char			**argv;
	char			**cmd;
	char			**env;
	char			**paths;
	char			exec_dir[300];
	char			exec_file[300];
	int				fd[2];
	int				ft_std[2];
	int				num;
	int				status;
	pid_t			*pids;
	int				enable;
	int				flag;
	int				p_i;
	int				p_j;
	int				p_nb;
	int				is_cflage;
	int				is_cmd;
	int				check_open;
	int				start;
	int				max_idx;
	char			*env_tem;
	int				env_start;
}					t_data;

typedef struct		s_termcap{
	int				c;
	char			*str;
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
	int				rs_len;
}					t_termcap;

t_termcap			g_t;

int					ft_read_str(char *buf);
void				ft_free(char **array);
void				ft_cmd_free(t_data *d);
void				ft_get_cmdlen(t_data *d);
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
int					ft_check_escape_num(char *str, int i);
void				ft_check_word(t_data *d, char *str, int *i);
void				ft_check_argv(t_data *d, char *str);
void				ft_check_pipe(t_data *d, char *str);

void				ft_check_env(t_data *d);
void				ft_put_env(t_data *d, char *str, int *i);
void				ft_put_env_0(t_data *d, char *str, int *i);
void				ft_put_env_1(char *str, int *i);
void				ft_put_env_2(t_data *d, char *str, int *i);
void				ft_check_env_rs(char *str, int *j);
void				ft_put_env_value_2
						(t_data *d, char *str, int *end, int start);
void				ft_put_env_value_1
						(t_data *d, char *str, int *end, int start);
char				**ft_get_env(char **env);

int					ft_iscmd(t_data *d, int i);
void				ft_put_echo(t_data *d);
void				ft_have_cmd(t_data *d, int *i);
void				ft_put_cmd(t_data *d);
void				ft_non_cmd(t_data *d, int *i);

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

int					ft_read_term(void);
int					putchar_tc(int tc);
void				ft_insert_char(void);
void				ft_backspace_char(void);
int					ft_history_len(void);
void				ft_term_left(void);
void				ft_term_right(void);
void				ft_term_backspace(void);
void				ft_term_delete(void);
void				ft_term_write(void);
void				ft_term_enter(void);
void				ft_term_up(void);
void				ft_term_down_1(void);
void				ft_term_down_2(void);
void				ft_term_d(void);

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
int					execfile_in_path(t_data *data, char *path);
void				over_write(t_data *data, char *key_value, int idx);
void				signal_handler(int signum);
int					is_valid(t_data *data);
int					add_operation(char *str);

int					check_head_valid(t_data *data);
int					check_other_valid(t_data *data);
void				err_messag(t_data *d, int *fx, int fd, int idx);
int					err_message(t_data *d);
void				ready_for_execute(int *fx, int fd, int idx);
int					cur(int x);
void				process_exit(t_data *data);
int					ft_relative_path_check(t_data *data, t_path_var *var);
#endif
