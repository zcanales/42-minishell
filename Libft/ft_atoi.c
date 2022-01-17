/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:52:22 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/17 18:40:58 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int				neg;
	int				i;
	unsigned int	sum;

	sum = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit((int)str[i]))
		sum = (sum * 10) + (str[i++] - '0');
	if ((sum > 2147483647 && neg == 1) || (sum > 2147483648 && neg == -1))
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	return (sum * neg);
}
