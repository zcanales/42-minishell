/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:44:11 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/19 21:42:41 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_error_pipe(char **orders)
{
	int	i;
	int	j;

	j = -1;
	while (orders[++j])
	{
		i = -1;
		while (orders[j][++i] && orders[j][i] == ' ')
			continue ;
		if (orders[j][i] == '\0')
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	pipes_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd("Pink peanuts:", 2);
		ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && line[i + 1] == '\0')
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}
