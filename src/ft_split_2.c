/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:49:32 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/03 20:34:14 by eperaita         ###   ########.fr       */
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
	size_t	start;

	i = 0;
	a = 0;
	while (s[i] && a < num_arrays)
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
			{
				if (s[i] == 34)
				{
					 while (s[++i] && s[i] != 34)
						continue ;
				}
				else if (s[i] == 39)
				{
					 while (s[++i] && s[i] != 39)
						continue ;
				}
				i++;
			}
			p[a] = ft_substr(s, start, i - start);
			if (!p[a])
				return (ft_freepointer(p, num_arrays));
			a++;
		}
		if (s[i])
			i++;
	}
	p[a] = NULL;
	return (p);
}

size_t	ft_num_arrays(char *s, char c, int *nbr_array)
{
	size_t	i;
	size_t	n;

	i = -1;
	n = 1;
	while (s[++i])
	{
		if (s[i] == 34) //COMILLAS DOBLES
		{
			while (s[++i] && s[i] != 34 )
				continue ;
		}
		else if (s[i] == 39) //COMILLAS SIMPLES
		{
			while (s[++i] && s[i] !=  39)
				continue ;
		}
	//	check_quotes(s, &i);
		if (s[i] == c) //PIPE 
		{
			i++;
			if (s[i] && s[i] == c)
				exit(1);
			n++;
		}
		if (s[i] == '\0')
			break ;
	}
	*nbr_array = n;
	return (n);
}

char	**ft_split_2(char const *s, char c, int *nbr_array)
{
	char	**p;
	size_t	a;
	size_t	num_arrays;

	a = 0;
	if (!s)
		return (0);
	num_arrays = ft_num_arrays ((char *)s, c, nbr_array);
	p = (char **)malloc((num_arrays + 1) * sizeof(char *));
	if (!p)
		return (0);
	p = ft_fill(p, (char *)s, c, num_arrays);
	return (p);
}
