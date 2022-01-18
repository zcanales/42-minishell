/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:16:54 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/18 18:37:40 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Líneaa vacía
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
			write(2,"Pink peanuts: Syntax error near unexpected token '|'\n", 53);
			return (1);
		}
	}
	return (0);
}

//El primer caráccter no puede ser un pipe
//Después de un pipe se acaba a línea
static int	pipes_check(char *line)
{
	int	i;
	
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		write(2,"Pink peanuts: Syntax error near unexpected token '|'\n", 53);
		return (1);
	}
	i = -1;
	while(line[++i])
	{
		if (line[i] == '|' && line[i + 1] == '\0')
		{
			write(2,"Pink peanuts: Syntax error near unexpected token '|'\n", 53);
			return (1);
		}
	}
	return (0);
}


static int	three_brackets_check(char *line, char c, int *i)
{
	if (line[*i + 1] && line[*i + 1] == c)
	{
		if (line[*i + 2] && line[*i + 2] == c)
		{
			write(2,"Pink peanuts: Syntax error near unexpected token '|'\n", 53);
			return (1);
		}
		*i += 1;
	}
	*i += 1;
	return (0);
}
//Comprueba que no haya 3 piquitos seguidos(three_brackets) 
//Después mira que después de un piquito no se acabe la linea ni haya otro piquitos entre espacios.
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
				write(2,"Pink peanuts: Syntax error near unexpected token '|'\n", 53);
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
			write(2,"Pink peanuts: Syntax error near unexpected token '|'\n", 53);
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
