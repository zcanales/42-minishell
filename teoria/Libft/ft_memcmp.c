/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 13:44:15 by zcanales          #+#    #+#             */
/*   Updated: 2021/08/02 17:21:30 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr_s2;
	unsigned char	*ptr_s1;

	ptr_s2 = (unsigned char *)s2;
	ptr_s1 = (unsigned char *)s1;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*ptr_s2 != *ptr_s1)
			return (*ptr_s1 - *ptr_s2);
		ptr_s2++;
		ptr_s1++;
	}
	return (0);
}
