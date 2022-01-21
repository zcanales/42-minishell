/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:00:08 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/21 16:28:52 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char *s, int *index)
{
	int	i;
	int	equal;

	i = *index;
	equal = 0;
	if (s[i] == 34)
	{
		while (s[++i] && s[i] != 34)
			continue ;
	}
	else if (s[i] == 39)
	{
		while (s[++i] && s[i] != 39)
			continue ;
	}
	*index = i;
	return (equal);
}

void	decode_quotes(t_shell *shell, char **str, int *i, int *start)
{
	int		dollar_pos;
	char	quote;
	char	*dollar_var;

	quote = *(*str + (*i));
	*i += 1;
	while (*(*str + (*i)) && *(*str + (*i)) != quote)
	{
		if (*(*str + (*i)) == '$' && quote == 34)
		{
			dollar_pos = *i;
			dollar_var = expand_dollar(shell, *str, i);
			replace_dollar(str, dollar_pos, *i - dollar_pos, dollar_var);
			*i = dollar_pos + ft_strlen(dollar_var) - 1;
			free(dollar_var);
		}
		*i += 1;
	}
	shell->check = 1;
	*start += 1;
}

char	*fill_dollar(t_shell *shell, int *i, char *array)
{
	int		start;
	char	*dollar_var;

	start = *i;
	dollar_var = expand_dollar(shell, array, i);
	replace_dollar(&array, start, *i - start, dollar_var);
	*i = ft_strlen(dollar_var) + start - 1;
	free(dollar_var);
	if (*i < 0)
		*i += 1;
	return (array);
}

char	*fill_new_array(char *array, int *i, char *new_array, int start)
{
	char	*temp_new_array;
	int		check;

	check = 1;
	if (start == *i)
		check = 0;
	while (array[*i] && array[*i] != 34
		&& array[*i] != 39 && array[*i] != '$')
		*i += 1;
	if (array[*i] == '$' && (array[*i + 1] == '\0'
			|| array[*i + 1] == ' '))
		*i += 1;
	temp_new_array = ft_substr_strjoin(array, new_array, start, *i);
	return (temp_new_array);
}

void	fill_quote_utils(int *ch , t_shell *shell, int *i)
{
	if (*ch == 1)
		*ch = 0;
	if (shell->check)
		*i += 1;
}

char	**fill_quote_dollar(char **array, t_shell *shell, int nbr_array, int ch)
{
	int		a;
	int		i;
	int		start;
	char	**new_array;

	a = -1;
	new_array = (char **)ft_calloc(sizeof(char *), nbr_array + 1);
	while (ch && array[++a])
	{
		i = 0;
		while (array[a][i])
		{
			start = i;
			if (array[a][i] == 34 || array[a][i] == 39)
				decode_quotes(shell, &array[a], &i, &start);
			else if (array[a][i] == '$')
				array[a] = fill_dollar(shell, &i, array[a]);
			new_array [a] = fill_new_array(array[a], &i, new_array[a], start);
			fill_quote_utils(&ch, shell, &i);
			shell->check = 0;
		}
	}
	new_array[nbr_array] = NULL;
	free_double(array, ch);
	return (new_array);
}
