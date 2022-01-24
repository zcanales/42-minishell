# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 16:37:50 by eperaita          #+#    #+#              #
#    Updated: 2022/01/24 16:33:20 by eperaita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell

SRCS =	src/main.c\
		src/init.c\
		src/processes.c\
		src/path.c\
		src/child_info.c\
		src/execute.c\
		src/utils.c\
		src/clean_command.c\
		src/ft_split_2.c\
		src/here_doc.c\
		src/mom_builtins.c\
		src/terminal.c\
		src/child_builtins.c\
		src/cd_builtin.c\
		src/export_unset.c\
		src/quote.c\
		src/dollar.c\
		src/error.c\
		src/error_2.c\


OBJS = $(SRCS:.c=.o)

MAKE = make
PINK = \033[0;35m \033[1m
RED = \033[0;31m \033[1m
RESET = \033[0m

INCLUDE = include/minishell.h
LIB_A = Libft/libft.a

CC = gcc 
#RLFLAGS =	-I ~/.brew/opt/readline/include\
			-lreadline\
			-L ~/.brew/opt/readline/lib\#

PWD = ~/.brew/opt/readline
RLFLAGS =   -I $(PWD)/include\
            -lreadline\
            -L $(PWD)/lib\
#RLFLAGS =	-I/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/include\
			-lreadline\
			-L/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/lib\#

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

all: $(NAME) 

$(NAME): $(OBJS) $(LIB_A) 
	@$(CC) $(CFLAGS) $(RLFLAGS) $^ $(LIB_A) -I$(INCLUDE) -o $(NAME)
	@echo "🥜$(PINK)$(NAME) was created 🥜$(RESET)"

$(LIB_A) : Libft/*.c Libft/*.h
	@make -C Libft/ bonus

%.o: %.c  $(INCLUDE) $(LIB_A) $(SRCS)
	@$(CC) $(CFLAGS) -I $(PWD)/lib -I$(INCLUDE) -c $< -o $@ -I $(PWD)/include
#	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@#

clean : 
	@make -C Libft/ clean
	@rm -f $(OBJS)
	@echo "🐘$(RED)object files were deleted$(RESET)"

fclean : clean
	@rm -rf $(NAME)
	@make -C Libft/ fclean
	@echo "🐘🐘$(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY : re all fclean clean
