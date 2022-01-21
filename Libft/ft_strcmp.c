/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:06:38 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/20 17:53:37 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	c;

	c = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[c] && s2[c])
	{
		if (s1[c] != s2[c])
			return (0);
		c++;
	}
	if (s1[c] == '\0' && s2[c] == '\0')
		return (1);
	return (0);
}
