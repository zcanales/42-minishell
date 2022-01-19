/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:16:54 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/19 13:47:09 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	three_brackets_check(char *line, char c, int *i)
{
	if (line[*i + 1] && line[*i + 1] == c)
	{
		if (line[*i + 2] && line[*i + 2] == c)
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
			return (1);
		}
		*i += 1;
	}
	*i += 1;
	return (0);
}

static int 	brackets_check(char *line, char c)
{
	int	i;
	
	i = -1;
	while (line[++i])
	{
		if (line[i] == c)
		{
			if (three_brackets_check(line, c, &i))
				return (1);
			while (line[i] && line[i] == ' ' )
				i++;
			if (line[i] == '\0' || line[i] == '<' || line[i] == '>')
			{
				ft_putstr_fd("Pink peanuts:", 2);
				ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
				return (1);
			}
		}
	}
	return (0);
}

static int open_quote_check(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		check_quotes(line, &i);
		if (line[i] == '\0')
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	check_error(char *line)
{
	if	(pipes_check(line))
		return (1);
	if (brackets_check(line, '<'))
		return (1);
	if (brackets_check(line, '>'))
		return (1);
	if (open_quote_check(line))
		return (1);
	return (0);
}


void	status_error(char *str, int err)
{
	printf("Pink peanuts: %s\n", str);
	exit(err);

}
