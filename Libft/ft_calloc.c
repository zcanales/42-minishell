/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:54:34 by zcanales          #+#    #+#             */
/*   Updated: 2021/08/05 12:37:14 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr_s;

	ptr_s = malloc(size * nmemb);
	if (!ptr_s)
		return (NULL);
	ft_bzero(ptr_s, (nmemb * size));
	return (ptr_s);
}
