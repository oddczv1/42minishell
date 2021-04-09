# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngrch <youngrch@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 15:02:07 by youngrch          #+#    #+#              #
#    Updated: 2021/04/06 15:02:30 by youngrch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test

SRCS		= ./main.c ./util.c

OBJS		= $(SRCS:.c=.o)

RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make all -C ./libft
	$(CC) $(CFLAGS) -O0 -o $(NAME) $(OBJS) ./libft/libft.a

all : $(NAME)

clean :
	make clean -C ./libft
	$(RM) $(OBJS)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
