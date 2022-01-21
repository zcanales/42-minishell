/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 12:02:07 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/20 17:54:19 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	suma;

	i = ft_strlen(dest);
	j = ft_strlen(src);
	if (i < size && size > 0)
	{
		size = size - i - 1;
		suma = i + j;
		j = 0;
		while (src[j] && size != 0)
		{
			dest[i++] = src[j++];
			size--;
		}
		dest[i] = '\0';
		return (suma);
	}
	else
		return (size + j);
}
