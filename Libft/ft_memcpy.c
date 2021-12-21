/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 13:14:49 by zcanales          #+#    #+#             */
/*   Updated: 2021/08/02 16:20:13 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr_src;
	char	*ptr_dest;

	if (!dest && !src)
		return (NULL);
	ptr_src = (char *)src;
	ptr_dest = (char *)dest;
	while (n--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}
