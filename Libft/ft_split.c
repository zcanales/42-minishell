/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 18:36:44 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/11 14:49:17 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **s_new, int in_col)
{
	int	i;

	i = -1;
	while (++i < in_col)
		free(s_new[in_col]);
	free(s_new);
	return (NULL);
}

static int	ft_count_col(char const *s, char c)
{
	unsigned int	i;
	unsigned int	col;

	i = 0;
	col = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break ;
		while (s[i] != c && s[i])
			i++;
		col++;
	}
	return (col);
}

char	**ft_fill_2d_array(char **s_new, char c, const char *s, int col)
{
	int	a;
	int	len;

	a = -1;
	while (++a < col)
	{
		while (*s == c && *s)
			s++;
		len = 0;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		s_new[a] = ft_substr(&s[-len], 0, len);
		if (!s_new[a])
			return (ft_malloc_error(s_new, a));
	}
	s_new[a] = NULL;
	return (s_new);
}

char	**ft_split(char const *s, char c)
{
	int		colums;
	char	**snew;

	if (!s)
		return (NULL);
	colums = ft_count_col(s, c);
	snew = (char **)malloc(sizeof(char *) * (colums + 1));
	if (!snew)
		return (NULL);
	snew = ft_fill_2d_array(snew, c, s, colums);
	return (snew);
}
