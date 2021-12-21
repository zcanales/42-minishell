/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:50:58 by zcanales          #+#    #+#             */
/*   Updated: 2021/09/08 14:06:47 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr_s;
	int		i;

	i = 0;
	len = ft_strlen(s);
	ptr_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr_s)
		return (NULL);
	ft_strlcpy(ptr_s, s, len + 1);
	return (ptr_s);
}
