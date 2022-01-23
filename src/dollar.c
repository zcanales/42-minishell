/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:05:33 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/23 19:19:51 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//REPLACE_DOLLAR
//EXPAND_DOLLAR
//EXPANDED_RETURN
//FILL_DOLLAR
////All functions together find the $VAR, replace it in the string,
//and returns with the expanded variable and the pointer actualizated
//Case of $? -> gets the last status

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

static char	*expanded_return(t_shell *shell, char *dollar_var)
{
	int		a;
	char	*ex;

	a = -1;
	while (shell->my_env->env[++a])
	{
		if (!ft_strncmp(dollar_var, shell->my_env->env[a],
				ft_strlen(dollar_var)))
		{
			if (shell->my_env->env[a][ft_strlen(dollar_var)] == '=')
			{
				ex = ft_substr(shell->my_env->env[a], ft_strlen(dollar_var) + 1,
						ft_strlen(shell->my_env->env[a])
						- ft_strlen(dollar_var) + 1);
				free(dollar_var);
				return (ex);
			}
		}
	}
	free(dollar_var);
	ex = (char *)malloc(sizeof(char) * 1);
	if (!ex)
		status_error(strerror(errno), errno);
	ex[0] = '\0';
	return (ex);
}

char	*expand_dollar(t_shell *shell, char *str, int *i)
{
	char	*dollar_var;
	int		start;

	start = *i;
	*i += 1;
	if (str[*i] == '?')
	{	
		*i += 1;
		return (ft_itoa(shell->status));
	}
	if (str[*i] == '\0' || str[*i] == ' ' || str[*i] == 34)
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	dollar_var = ft_substr(str, start + 1, *i - start - 1);
	return (expanded_return(shell, dollar_var));
}

int	replace_dollar(char **str, int start, int len, char *replace)
{
	int		i;
	char	*temp;
	int		total_len;

	i = -1;
	total_len = ft_strlen(*str) - len + ft_strlen(replace);
	temp = (char *)ft_calloc(sizeof(char), total_len + 1);
	if (!temp)
		status_error(strerror(errno), errno);
	ft_strlcpy(temp, *str, start + 1);
	ft_strlcat(temp, replace, ft_strlen(replace) + ft_strlen(temp) + 1);
	ft_strlcat(temp, *str + start + len, total_len + 1);
	free(*str);
	*str = NULL;
	*str = ft_strdup(temp);
	free(temp);
	return (ft_strlen(replace));
}
