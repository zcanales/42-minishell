# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 09:49:26 by zcanales          #+#    #+#              #
#    Updated: 2022/01/03 11:12:04 by eperaita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	src/main.c\
		src/init.c\
		src/exe.c\
		src/terminal.c\
		src/attributes.c\
		src/utils.c\
		src/processes.c\

OBJS = $(SRCS:.c=.o)
OBJ_DIR = obj

MAKE = make
PINK = \033[0;35m \033[1m
RED = \033[0;31m \033[1m
RESET = \033[0m

INCLUDE = include/minishell.h
LIB_A = Libft/libft.a

CC = gcc
PWD_RL = /System/Volumes/Data/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/
RLFLAGS = -L /sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/lib\
		  -I /sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/include\
		  -lreadline\

CFLAGS = -Wall -Wextra -Werror
all: $(NAME) 

$(NAME): $(SRCS) $(LIB_A) 
	@$(CC) $(CFLAGS) $(RLFLAGS) $^ $(LIB_A) -I$(INCLUDE) -o $(NAME)
	@#@mv $(OBJS) $(OBJ_DIR)
	@echo "🥜$(PINK)$(NAME) was created 🥜$(RESET)"

$(OBJ_DIR):
	@mkdir $@

$(LIB_A) : Libft/*.c Libft/*.h
	@make -C Libft/

%.o: %.c $(OBJ_DIR) $(INCLUDE) $(LIB_A)
	if [ "$<" = "src/terminal.c" ];then\
		$(CC) $(RLFLAGS) -I$(INCLUDE) -c $< -o $@;\
	else\
		$(CC) $(FLAGS) -I$(INCLUDE) -c $< -o $@;\
	fi
#	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

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
