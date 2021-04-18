# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huchoi <huchoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 15:02:07 by youngrch          #+#    #+#              #
#    Updated: 2021/04/15 13:45:12 by huchoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test

SRCS		= ./main.c \
				./src/util.c \
				./src/check_mark.c \
				./src/parse_env.c \
				./src/parse.c \
				./src/process.c ./src/think.c \
				./src/for_echo.c ./src/for_env.c \
				./src/for_pwd.c  ./src/for_cd.c \
				./src/for_export.c ./src/for_unset.c \
				./src/utils_for_process.c ./src/get_path_exec_dir_file.c \


OBJS		= $(SRCS:.c=.o)

RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make all -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

all : $(NAME)

clean :
	make clean -C ./libft
	$(RM) $(OBJS)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
