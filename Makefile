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
			get_next_line_utils.c \
			get_next_norme.c
GNL		 =	$(addprefix $(GNL_PATH)/,$(GNL_NAME))

SRC_PATH =	./srcs
TMP		 =	main.c \
			ft_split.c \
			ft_splitv2.c \
			ft_builtins.c \
			ft_builtins_bis.c \
		 	ft_utils.c \
		 	ft_utils2.c \
			ft_env.c \
			ft_builtins2.c \
			ft_builtins2_bis.c \
			ft_builtins2_bis_bis.c \
			ft_builtins2v4.c \
			ft_check.c \
			semicolon.c \
			ft_redir.c \
			ft_redir2.c \
			ft_free.c \
			ft_exec.c \
			main_loop.c \
			ft_pipe.c \
			ft_pipes2.c \
			ft_norme.c \
			ft_norme2.c \
			ft_norme3.c \
			ft_norme4.c \
			for_exit.c

SRC_NAME =	$(TMP) $(GNL)
SRC      =	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

P_LIB	 =	srcs/libftprintf.a
P_PATH	 =	srcs/printf

#	Objects   #
OBJ_PATH =	./.objs
OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ      =	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#  Some Vars  #
DEP  = $(OBJ:%.o=%.d)
COLOR = \e[38;5;140m
RESET = \e[0m
CHECK = 0

# unecessary vars  #
SCRIPT_P =	./scripts

################################################################################

all : $(NAME)
#	@sh scripts/test.sh

f : $(NAME)

#header1 :
#	@sh $(SCRIPT_P)/print_header.sh

#header2 :
#	@sh $(SCRIPT_P)/print_header2.sh


$(NAME) : header $(OBJ) bottom
	@make -C $(P_PATH)
	@$(CC) $(CFLAGS) $(P_LIB) $(OBJ) -o $@

clear :
	@printf "\ec"

bottom :
	@printf "$(COLOR)#                                                             #\n"
	@printf "#                             \e[1;36mDONE\e[0m$(COLOR)                            #\n"
	@printf "#                                                             #\n"
	@printf "###############################################################$(RESET)\n\n"

header : clear
	@printf "$(COLOR)###############################################################\n"
	@printf "#                                                             #\n"
	@printf "#                          \e[1;36mMINISHELL\e[0m$(COLOR)                          #\n"
	@printf "#                                                             #\n"
	@printf "###############################################################$(RESET)\n"

-include $(DEP)
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/$(GNL_PATH)
	@$(CC) $(CFLAGS) -MMD -I$(HEADER_P) -o $@ -c $<
	@printf "$(COLOR)#$(RESET) \e[1;30m$(CC): \e[1;37m./%-42s\e[1;0m" "$<"
	@printf "\e[32mCompiled √\e[1;0m $(COLOR)#$(RESET)\n"

debug : fclean header $(OBJ) bottom
	@make -C $(P_PATH)
	@$(CC) $(CFLAGS) $(DEBUG) $(P_LIB) $(OBJ) -o $@

clean : clear
	@make -C $(P_PATH) clean
	@rm -rf $(OBJ_PATH) 
	@printf "Cleaning files . "
	@sleep 0.5
	@printf "\rCleaning files . . "
	@sleep 0.5
	@printf "\rCleaning files . . . "
	@sleep 0.5
	@printf "\r"

save : fclean
	git add .
	git commit -m "$m"
	git push

fclean : clean
	@rm -rf $(NAME)
	@rm -rf debug
	@make -C $(P_PATH) fclean

re : fclean all

.PHONY: all clean fclean re
