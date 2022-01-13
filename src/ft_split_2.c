/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:49:32 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/13 20:06:11 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_freepointer(char **p, int *num_arrays)
{
	int i;

	i = 0;
	while (i < (*num_arrays + 1))
	{
		free(&p[i]);
		i++;
	}
	free(p);
	return (0);
}

char	**ft_fill(char **p, char *s, char c, int *num_arrays)
{
	int		a;
	int		i;
	size_t	start;

	i = 0;
	a = 0;
	while (s[i] && a < *num_arrays)
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
			{
				check_quotes(s, &i);
				i++;
			}
			p[a] = ft_substr(s, start, i - start);
			if (!p[a])
				return (ft_freepointer(p, num_arrays));
			a++;
		}
		if (s[i] == c)
			i++;
	}
	p[a] = NULL;
	return (p);
}

void	ft_num_arrays(char *s, char c, int *nbr_array)
{
	int	i;
	
	*nbr_array = 1;
	i = -1;
//	printf("split --> %s y el char = %d\n", &s[i], c);
	while (s[++i])
	{
//		printf("split --> %s y el char = %d\n", &s[i], c);
		check_quotes(s, &i);
		if (s[i] == c) 
		{
			if (s[i + 1] && s[i + 1] == '|') 
			{				//ERROR: EN CASO DE 2 || SEGUIDAS
				printf("Error: 2 pipes not allowed\n");
				exit(1);
			}
			if (s[i + 1] && s[i + 1] == c && c != 32) //si es dos piquitos solo cuenta 1
				i++;
			*nbr_array +=1;
		}
//		if (!s[i])
//			break ;
	}
}

char	**ft_split_2(char const *s, char c, int *nbr_array)
{
	char	**p;
	size_t	a;

	a = 0;
	if (!s)
		return (0);
	ft_num_arrays ((char *)s, c, nbr_array);
	p = (char **)malloc((*nbr_array + 1) * sizeof(char *));
	if (!p)
		return (0);
	p = ft_fill(p, (char *)s, c, nbr_array);
//	p[*nbr_array] = NULL;
	if (c != '|' && c != 32) 
		*nbr_array = *nbr_array - 1;
	return (p);
}
