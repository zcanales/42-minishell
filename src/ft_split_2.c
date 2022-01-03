/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:49:32 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/03 17:33:45 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_freepointer(char **p, size_t num_arrays)
{
	size_t	i;

	i = 0;
	while (i < (num_arrays + 1))
	{
		free(&p[i]);
		i++;
	}
	free(p);
	return (0);
}

char	**ft_fill(char **p, char *s, char c, size_t num_arrays)
{
	size_t	a;
	size_t	i;
	size_t	j;

	i = 0;
	a = 0;
	while (a < num_arrays && s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] && s[i] != c)
			{
				if (s[i] == 34)
				{
					 while (s[++i] != 34)
						continue ;
				}
				else if (s[i] == 39)
				{
					 while (s[++i] != 39)
						continue ;
				}
				i++;
			}
			p[a] = ft_substr(s, j, i - j);
			if (!p[a])
				return (ft_freepointer(p, num_arrays));
			a++;
		}
		i++;
	}
	p[a] = NULL;
	return (p);
}

size_t	ft_num_arrays(char *s, char c)
{
	size_t	i;
	size_t	n;

	i = -1;
	n = 0;
	while (s[++i])
	{
		if (s[i] == 34)
		{
			printf("%c\n", s[i]);
			while (s[++i] != 34 )
				continue ;
		}
		else if (s[i] == 39)
		{
			while (s[++i] !=  39)
				continue ;
		}
		else if (s[i] == c)
		{
			i++;
			if (s[i] && s[i] == c)
				exit(1);
		}
		else
		{
			while (s[i] && s[i] != c && s[i] != 34)
				i++;
			n++;
		}
	}
	return (n);
}

char	**ft_split_2(char const *s, char c)
{
	char	**p;
	size_t	a;
	size_t	num_arrays;

	a = 0;
	if (!s)
		return (0);
	num_arrays = ft_num_arrays ((char *)s, c);
	p = (char **)malloc((num_arrays + 1) * sizeof(char *));
	if (!p)
		return (0);
	p = ft_fill(p, (char *)s, c, num_arrays);
	return (p);
}
