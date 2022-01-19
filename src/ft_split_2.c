/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:49:32 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/19 15:44:39 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_freepointer(char **p, int *num_arrays)
{
	int	i;

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
	return (p);
}

void	ft_num_arrays(char *s, char c, int *nbr_array)
{
	int	i;

	*nbr_array = 1;
	i = -1;
	while (s[++i])
	{
		check_quotes(s, &i);
		if (s[i] == c)
		{
			if (s[i + 1] && s[i + 1] == '|')
				status_error("Pink peanuts: 2 pipes not allowed\n", 1);
			if (s[i + 1] && s[i + 1] == c && c != 32)
				i++;
			*nbr_array += 1;
		}
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
	p = (char **)ft_calloc(sizeof(char *), (*nbr_array + 1));
	if (!p)
		status_error(strerror(errno), errno);
	p = ft_fill(p, (char *)s, c, nbr_array);
	if (c != '|' && c != 32)
		*nbr_array = *nbr_array - 1;
	return (p);
}
