/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 15:50:42 by zcanales          #+#    #+#             */
/*   Updated: 2021/08/06 13:05:41 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!*lst)
		return ;
	temp = *lst;
	while (temp)
	{
		temp = temp->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}
