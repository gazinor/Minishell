NAME     =	Minishell

# 	Compiler  #
CC       =	gcc

#	Flags     #
CFLAGS   =	-Wall -Wextra -Werror 
DEBUG	 = -g3 -fsanitize=address

# 	Headers   #
HEADER_P = 	./includes
HEADER_N =	minishell.h \
			ft_printf.h \
			get_next_line.h
HEADER   =	$(addprefix $(HEADER_P)/,$(HEADER_N))

#	Sources   #
GNL_PATH =	gnl
GNL_NAME =	get_next_line.c \
			get_next_line_utils.c
GNL		 =	$(addprefix $(GNL_PATH)/,$(GNL_NAME))

SRC_PATH =	./srcs
TMP		 =	main.c \
			ft_split.c \
			ft_builtins.c \
		 	ft_utils.c \
			ft_env.c \
			ft_builtins2.c
SRC_NAME =	$(TMP) $(GNL)
SRC      =	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

P_LIB	 =	srcs/libftprintf.a
P_PATH	 =	srcs/printf

#	Objects   #
OBJ_PATH =	./.objs
OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ      =	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

DEP  = $(OBJ:%.o=%.d)

# unecessary vars  #
SCRIPT_P =	./scripts

################################################################################

all : $(NAME)

f : $(NAME)

#header1 :
#	@sh $(SCRIPT_P)/print_header.sh

#header2 :
#	@sh $(SCRIPT_P)/print_header2.sh


$(NAME) : $(OBJ)
	@make -C $(P_PATH)
	@$(CC) $(CFLAGS) $(P_LIB) $(OBJ) -o $@

-include $(DEP)
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/$(GNL_PATH)
	@$(CC) $(CFLAGS) -MMD -I$(HEADER_P) -o $@ -c $<
	@printf "\e[1;30m$(CC): \e[1;37m./%-51s\e[1;0m" "$<"
	@printf "\e[32mcheck\e[1;0m\n"

debug : fclean $(OBJ)
	@make -C $(P_PATH)
	@$(CC) $(CFLAGS) $(DEBUG) $(P_LIB) $(OBJ) -o $@

clean :
	@make -C $(P_PATH) clean
	@rm -rf $(OBJ_PATH) 
	@printf "Cleaning files ."
	@sleep 0.5
	@printf "\rCleaning files . ."
	@sleep 0.5
	@printf "\rCleaning files . . .\r"
	@sleep 0.5

save : fclean
	git add .
	git commit -m "$m"
	git push

fclean : clean
	@rm -rf $(NAME)
	@make -C $(P_PATH) fclean

re : fclean all

.PHONY: all clean fclean re
