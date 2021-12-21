/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 13:39:43 by zcanales          #+#    #+#             */
/*   Updated: 2021/08/02 13:51:30 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*ptr_src;

	ptr_src = (unsigned char *)src;
	while (n--)
	{
		if (*ptr_src == (unsigned char) c)
			return (ptr_src);
		ptr_src++;
	}
	return (NULL);
}
