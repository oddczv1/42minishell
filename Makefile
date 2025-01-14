# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 15:02:07 by youngrch          #+#    #+#              #
#    Updated: 2021/04/26 20:49:28 by huchoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS		= ./main.c \
				./src/util.c \
				./src/utils_for_parse_1.c \
				./src/utils_for_parse_2.c \
				./src/utils_for_free.c \
				./src/check_mark.c \
				./src/parse_env_1.c \
				./src/parse_env_2.c \
				./src/parse.c \
				./src/termcap.c \
				./src/termcap_key_util_1.c \
				./src/termcap_key_util_2.c \
				./src/redirection_1.c \
				./src/redirection_2.c \
				./src/for_echo.c \
				./src/for_env.c \
				./src/pipe.c \
				./src/process.c \
				./src/pipe_line.c \
				./src/for_pwd.c \
				./src/for_cd.c \
				./src/for_export.c \
				./src/for_unset.c \
				./src/utils_for_process.c \
				./src/get_path_exec_dir_file.c \
				./src/for_env_2.c ./src/for_bash.c \
				./src/get_path_exec_dir_file_utils.c \
				./src/for_export_2.c ./src/pipe_line_2.c \
				./src/for_exit.c ./src/for_exit_utils.c \
				./src/pipe_line_3.c

OBJS		= $(SRCS:.c=.o)

RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make all -C ./libft
	$(CC) $(CFLAGS) -lncurses -o $(NAME) $(OBJS) ./libft/libft.a

all : $(NAME)

clean :
	make clean -C ./libft
	$(RM) $(OBJS)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
