# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 16:37:50 by eperaita          #+#    #+#              #
#    Updated: 2022/01/19 13:45:33 by eperaita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell

SRCS =	src/main.c\
		src/init.c\
		src/processes.c\
		src/child_info.c\
		src/execute.c\
		src/utils.c\
		src/clean_command.c\
		src/ft_split_2.c\
		src/here_doc.c\
		src/mom_builtins.c\
		src/terminal.c\
		src/child_builtins.c\
		src/export_unset.c\
		src/quote_dollar.c\
		src/error.c\
		src/error_2.c\


OBJS = $(SRCS:.c=.o)
OBJ_DIR = obj

MAKE = make
PINK = \033[0;35m \033[1m
RED = \033[0;31m \033[1m
RESET = \033[0m

INCLUDE = include/minishell.h
LIB_A = Libft/libft.a

CC = gcc
PWD_RL =	/System/Volumes/Data/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/
RLFLAGS =	-I/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/include\
			-lreadline\
			-L/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/lib\

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME) 

$(NAME): $(OBJS) $(LIB_A) 
	@$(CC) $(CFLAGS) $(RLFLAGS) $^ $(LIB_A) -I$(INCLUDE) -o $(NAME)
	@mv $(OBJS) $(OBJ_DIR)
	@echo "🥜$(PINK)$(NAME) was created 🥜$(RESET)"

$(OBJ_DIR):
	@mkdir $@

$(LIB_A) : Libft/*.c Libft/*.h
	@make -C Libft/ bonus

%.o: %.c $(OBJ_DIR) $(INCLUDE) $(LIB_A)
	@$(CC) -I$(INCLUDE) -c $< -o $@

clean :
	@rm -rf obj/
	@make -C Libft/ clean
	@echo "🐘$(RED)object files were deleted$(RESET)"

fclean : clean
	@rm -rf $(NAME)
	@make -C Libft/ fclean
	@echo "🐘🐘$(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY : re all fclean clean
