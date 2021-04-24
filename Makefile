# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 15:02:07 by youngrch          #+#    #+#              #
#    Updated: 2021/04/24 15:45:03 by huchoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS		= ./main.c \
				./src/util.c \
				./src/utils_for_parse.c \
				./src/check_mark.c \
				./src/parse_env.c \
				./src/parse.c \
				./src/termcap.c \
				./src/termcap_key_util_1.c \
				./src/termcap_key_util_2.c \
				./src/redirection.c \
				./src/for_echo.c \
				./src/for_env.c \
				./src/pipe.c \
				./src/process.c \
				./src/think.c \
				./src/for_pwd.c \
				./src/for_cd.c \
				./src/for_export.c \
				./src/for_unset.c \
				./src/utils_for_process.c \
				./src/get_path_exec_dir_file.c \
				./src/for_env_2.c ./src/for_bash.c \
				./src/get_path_exec_dir_file_utils.c \
				./src/for_export_2.c ./src/think_2.c


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
