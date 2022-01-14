/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:50:58 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/14 13:45:28 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr_s;
	int		i;

	i = -1;
	len = ft_strlen(s);
	ptr_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr_s)
		return (NULL);
	while (s[++i])
		ptr_s[i] = s[i];
	ptr_s[i] = '\0';
	return (ptr_s);
}
