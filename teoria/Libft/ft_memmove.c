/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 13:27:03 by zcanales          #+#    #+#             */
/*   Updated: 2021/08/02 17:28:57 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptr_src;
	char	*ptr_dest;

	if (!dest && !src)
		return (NULL);
	ptr_src = (char *)src;
	ptr_dest = (char *)dest;
	if (ptr_dest > ptr_src)
	{
		ptr_dest = ptr_dest + n - 1;
		ptr_src = ptr_src + n - 1;
		while (n--)
			*ptr_dest-- = *ptr_src--;
	}
	else
	{
		while (n--)
			*ptr_dest++ = *ptr_src++;
	}
	return (dest);
}
