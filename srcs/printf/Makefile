# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glaurent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 17:12:19 by glaurent          #+#    #+#              #
#    Updated: 2019/11/18 23:04:41 by glaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
SRCS :=	ft_case_c.c \
		ft_case_dni.c \
		ft_case_indetermination.c \
		ft_case_p.c \
		ft_case_pct.c \
		ft_case_s.c \
		ft_case_u.c \
		ft_case_x.c \
		ft_case_x_big.c \
		ft_printf.c \
		ft_utils.c \
		ft_utils2.c

INCLUDES = ./
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES) 

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY :	clean	all	fclean	re	test
