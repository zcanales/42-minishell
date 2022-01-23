/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:16:54 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/23 19:27:18 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CHECK_ERROR -> Handle the error and prints and RETURN
	//THREE_BRACKET_CHECK -> <<<
	//BRACKETS_CHECK -> |<
	//OPEN_QUOTE_CHECK -> open quotes
	//(error_2.c)
//STATUS_ERROR -> Prints the error in str an EXIT

static int	three_brackets_check(char *line, char c, int *i)
{
	if (line[*i + 1] && line[*i + 1] == c)
	{
		if (line[*i + 2] && line[*i + 2] == c)
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error near unexpected token 'newline'\n", 2);
			return (1);
		}
		*i += 1;
	}
	*i += 1;
	return (0);
}

static int	brackets_check(char *line, char c)
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
			if (line[i] == '\0' || line[i] == '<' || line[i] == '>'
				|| line[i] == '|')
			{
				ft_putstr_fd("Pink peanuts:", 2);
				ft_putstr_fd("Syntax error near unexpected token 'newline'\n",
					2);
				return (1);
			}
		}
	}
	return (0);
}

static int	open_quote_check(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		check_quotes(line, &i);
		if (line[i] == '\0')
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(" Syntax error, unclosed quotes\n", 2);
			return (1);
		}
	}
	return (0);
}

int	check_error(char *line)
{
	if (check_line_empty(line))
		return (1);
	if (brackets_check(line, '<'))
		return (1);
	if (brackets_check(line, '>'))
		return (1);
	if (open_quote_check(line))
		return (1);
	if (check_two_pipe(line))
		return (1);
	return (0);
}

void	status_error(char *str, int err)
{
	ft_putstr_fd("Pink peanuts: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(err);
}
