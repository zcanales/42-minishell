/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:45:59 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/07 20:39:52 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	unsigned int	malloc_len;
	size_t			s_len;

	if (!s)
		return (NULL);
	malloc_len = 0;
	s_len = ft_strlen(s);
	if (start < s_len)
		malloc_len = s_len - start;
	if (malloc_len > len)
		malloc_len = len;
	s2 = (char *)malloc(sizeof(char) * (malloc_len + 1));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s + start, malloc_len + 1);
	return (s2);
}
