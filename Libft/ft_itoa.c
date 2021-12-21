/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:01:50 by zcanales          #+#    #+#             */
/*   Updated: 2021/10/06 11:51:47 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	int		len;
	long	nbr;

	len = 1;
	nbr = n;
	if (nbr < 0)
	{
		nbr = nbr *(-1);
		len++;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*ptr_s;
	int		negative;
	long	nbr;

	negative = 0;
	len = ft_len(n);
	nbr = n;
	if (n < 0)
	{
		nbr = nbr * (-1);
		negative = 1;
	}
	ptr_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr_s)
		return (NULL);
	ptr_s[len] = '\0';
	while (len--)
	{
		ptr_s[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (negative)
		ptr_s[0] = '-';
	return (ptr_s);
}
