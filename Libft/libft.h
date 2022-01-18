/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 12:52:50 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/18 19:27:39 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*prev;
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t n);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*f)(void*));	
t_list			*ft_lstnew(void	*content);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void*));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(
					t_list *lst, void *(*f)(void *), void (*del)(void *));
void			*ft_memchr(const void *src, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
size_t			ft_strlcpy(char *dest, const char *str, size_t size);
size_t			ft_strlen(const char	*str);
char			*ft_strrchr(const char *s, int c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif
