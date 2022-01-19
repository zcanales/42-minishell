/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:39:56 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/19 12:23:44 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FT_SUB_JOIN
char	*ft_substr_strjoin(char *to_sub, char *to_join, int start, int end)
{
	char	*real_temp;
	char	*temp;

	temp = ft_substr(to_sub, start, end - start);
	if (!to_join)
		real_temp = ft_strdup(temp);
	else
	{
		real_temp = ft_strjoin(to_join, temp);
		free(to_join);
	}
	free(temp);
	return (real_temp);
}

//FREE_DOUBLE//
void	free_double(char **s, int check)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	if (check == 2)
		free(s);
}

//FREELIST///
void	ft_freelist(t_list **head)
{
	t_list	*temp;

	if (!*head)
		return ;
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free (temp);
	}
	*head = NULL;
}

/*CONVERT ARRAY TO STRING*/
char	*convert_array_to_string(char **array)
{
	char	*string;

	string = ft_strdup(array[0]);
	free_double(array, 2);
	return (string);
}
