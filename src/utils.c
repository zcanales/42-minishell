/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:39:56 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/03 16:47:38 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CLOSE PIPES//

void close_pipes(t_shell *shell)
{
	int i;
    int j;
	
	i = 0;
    while (i < shell->my_pro->nprocess + 1)
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
