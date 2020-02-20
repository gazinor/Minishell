# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glaurent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 17:12:19 by glaurent          #+#    #+#              #
#    Updated: 2020/02/20 22:34:48 by glaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ../libftprintf.a
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

INCLUDES = ../../includes/

OBJ_PATH = ./.objs
OBJ_NAME = $(SRCS:.c=.o)
OBJS      =  $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES) 

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJ_PATH)/%.o : %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean :
	@rm -rf $(OBJ_PATH) $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY :	clean	all	fclean	re
