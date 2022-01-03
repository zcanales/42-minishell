/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:39:56 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/03 20:34:17 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CLOSE PIPES//

void close_pipes(t_shell *shell)
{
	int i;
    int j;
	
	i = 0;
    while (i < shell->my_pro->nbr_process + 1)
    {
        j = 0;
        while (j < 2)
        {
            close(shell->my_pro->fd[i][j]);
            j++;
        }
        i++;
    }
}

void	check_quotes(char *s, size_t *index)
{
	int i;

	i = *index;
	if (s[i] == 34)
	{
		while (s[i] != 34)
			continue ;
	}
	else if (s[i] == 39)
	{
		while (s[++i] != 39)
			continue ;
	}
	*index = i;
}
