/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:02:54 by zcanales          #+#    #+#             */
/*   Updated: 2021/08/03 09:58:54 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*s1;
	size_t	i;

	i = -1;
	if (!s)
		return (NULL);
	s1 = ft_strdup(s);
	if (!s1)
		return (NULL);
	while (s[++i])
		s1[i] = f(i, s[i]);
	s1[i] = '\0';
	return (s1);
}
