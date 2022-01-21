/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:44:11 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/21 12:36:19 by zcanales         ###   ########.fr       */
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

int	check_line_empty(char *line)
{
	char *new;
	
	new = ft_strtrim(line, " ");
	if (new[0] == '\0')
	{
		ft_free(new);
		return (1);
	}
	ft_free(new);
	return (0);
}

void	printf_error(char *s, int err)
{
	ft_putstr_fd("Pink peanuts: '", 2);
	ft_putstr_fd(s, 2);
	if (err == 1)
		ft_putstr_fd("' not a valid identifier\n", 2);
	if (err == 2)
		ft_putstr_fd("': Command not found\n", 2);
}
