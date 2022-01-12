# **************************************************************************** #
#                                                                              #
#                                                           :::      ::::::::  #
#  Makefile                                               :+:      :+:    :+:  #
#                                                       +:+ +:+         +:+    #
#  By: zcanales <zcanales@student.42urduliz.com>      +#+  +:+       +#+       #
#                                                   +#+#+#+#+#+   +#+          #
#  Created: 2021/07/22 12:11:18 by zcanales              #+#    #+#            #
#  Updated: 2021/08/02 11:21:53 by zcanales             ###   ########.fr      #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = 	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putstr_fd.c\
		ft_putnbr_fd.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strcmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_split.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\

OBJS =	$(SRC:.c=.o)

BONUS = ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\

OBJS_BONUS = $(BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
LIB = ar rcs

all : $(NAME)

$(NAME) : $(OBJS)
	@$(LIB) $(NAME) $(OBJS)

bonus: $(OBJS_BONUS) $(OBJS)
	@$(LIB) $(NAME) $(OBJS)  $(OBJS_BONUS)

%.o : %.c
	@$(CC) $(CFLAGS) -I libft.h -g -c $< -o $@
clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all 

.PHONY : all clean fclean re bonus 
