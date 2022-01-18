/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:00:08 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/18 19:08:49 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//EXPORT
//CHECK_QUOTES//
//EXPORT_NAME -> Aloja lo que hay detras del export completo (a=hola$USER),(Si no es sintaxis ok -> no aloja)
//GET_REAL_VARIABLE -> Recompone el array de variables ok en real_var: DECODE_QUOTES + EXPAND_DOLLAR y va pegando los cachos (texto, comillas, var)
//**DECOCE_QUOTES -> Quita las comillas (siempre que cierren)
//**EXPAND_DOLLAR -> Expande la variable $ y la reemplaza siempre qque exista ya alojada en env
//****FT_REPLACE_VAR -> Trocea la string, y copia en la nueva var_real cacho pre + variable desde env  + cacho post
//**FT_SUBSTR_STRJOIN -> saca un cacho y lo junta a la real_var actual


int	check_quotes(char *s, int *index)
{
	int i;
	int equal;

	i = *index;
	equal = 0;
	if (s[i] == 34)
	{
		while (s[++i] && s[i] != 34)
			continue;
	}
	else if (s[i] == 39)
	{
		while (s[++i] && s[i] != 39)
			continue;
	}
	*index = i;
	return (equal);
}

char *expand_dollar(t_shell *shell, char *str, int *i)
{
	int a;
	char *expanded;
	char *dollar_var;
	int	start;

	start = *i;
	a = -1;
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
	dollar_var = ft_substr(str, start + 1, *i - start - 1); // dollar_var = variable
	while (shell->my_env->env[++a]) //buscarla en env
	{
		if (!ft_strncmp(dollar_var, shell->my_env->env[a], ft_strlen(dollar_var)))
		{
			if(shell->my_env->env[a][ft_strlen(dollar_var)] == '=')
			{
				expanded = ft_substr(shell->my_env->env[a], ft_strlen(dollar_var) + 1, ft_strlen(shell->my_env->env[a]) - ft_strlen(dollar_var) + 1);
				return(expanded);
			}
		}
	}
	expanded = (char *)malloc(sizeof(char) * 1);
	if (!expanded)
		status_error(strerror(errno), errno);
	expanded[0] = '\0';
	return (expanded);
}

int	replace_dollar(char **str, int start, int len, char *replace)
{
	int i;
	char *temp;
	int total_len;

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

void	decode_quotes(t_shell *shell, char **str, int *i) 
{
    int     start;
    int     dollar_pos;
	char	quote;
	char	*dollar_var;

	quote = *(*str + (*i));
	*i += 1;
    start = *i;
    while (*(*str + (*i)) && *(*str + (*i)) != quote)
	{
		if (*(*str + (*i)) == '$' && quote == 34)
		{
			dollar_pos = *i;
			dollar_var = expand_dollar(shell, *str, i);
			replace_dollar(str, dollar_pos, *i - dollar_pos, dollar_var);
			*i = dollar_pos + ft_strlen(dollar_var) - 1;
		}
		*i += 1;
	}
}


char **fill_quote_dollar(char **array, t_shell *shell, int nbr_array, int check)
{
	int a;
	int	i;
	int start;
	char **new_array;
	char *dollar_var;
	
	a = -1;
    new_array = (char **)ft_calloc(sizeof(char *), nbr_array + 1);   
  	if (!new_array)
		status_error(strerror(errno), errno);
	while (check && array[++a]) 
	{
		i = 0;
		while (array[a][i])
		{
			start = i;
			if (array[a][i] == 34 || array[a][i] == 39)
			{
				decode_quotes(shell,  &array[a], &i);
				start++;
			}
			else if (array[a][i] == '$')
			{
				start = i;
				dollar_var = expand_dollar(shell, array[a], &i);
				replace_dollar(&array[a], start, i - start, dollar_var);
				i = ft_strlen(dollar_var) + start - 1;
				if (i < 0)
					i++;
			}
			while (array[a][i] && array[a][i] != 34 && array[a][i] != 39 && array[a][i] != '$')
				i++;
			if (array[a][i] == '$' && (array[a][i + 1] == '\0' || array[a][i + 1] == ' '))
					i += 1;
			new_array[a] = ft_substr_strjoin(array[a], new_array[a], start, i);
			if (check == 1)
				check = 0;
		}
	}
	new_array[nbr_array] = NULL;
	free_double(array, check);
	array = NULL;
	return (new_array);
}



