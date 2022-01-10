/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:16:54 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/10 14:21:00 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_error_pipe(char **orders)
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
			printf("syntax error near unexpected token '|'\n");
			exit(1);
		}
	}
}

static void	pipes_check(char *line)
{
	int	i;
	
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("syntax error near unexpected token '|'\n");
		exit(1);
	}
	i = -1;
	while(line[++i])
	{
		if(line[i] == '|' && line[i + 1] == '\0')
		{
			printf("syntax error near unexpected token '|'\n");
			exit(1);
		}
	}
}


static void	three_brackets_check(char *line, char c, int *i)
{
	if (line[*i + 1] && line[*i + 1] == c)
	{
		if (line[*i + 2] && line[*i + 2] == c)
		{
			printf("syntax error near unexpected token 'newline'\n");
			exit(1);
		}
		*i += 1;
	}
	*i += 1;
}

static void	brackets_check(char *line, char c)
{
	int	i;
	
	i = -1;
	while (line[++i])
	{
		if (line[i] == c)
		{
			three_brackets_check(line, c, &i);
			while (line[i] && line[i] == ' ' )
				i++;
			if (line[i] == '\0' || line[i] == '<' || line[i] == '>')
			{
				printf("syntax error near unexpected token 'newline'\n");
				exit(1);
			}
		}
	}
}

void	check_error(char *line)
{
	pipes_check(line);
	brackets_check(line, '<');
	brackets_check(line, '>');
}
