/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:00:08 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/12 14:18:24 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//EXPORT
//EXPORT_NAME -> Aloja lo que hay detras del export completo (a=hola$USER),(Si no es sintaxis ok -> no aloja)
//GET_REAL_VARIABLE -> Recompone el array de variables ok en real_var: DECODE_QUOTES + EXPAND_DOLLAR y va pegando los cachos (texto, comillas, var)
//**DECOCE_QUOTES -> Quita las comillas (siempre que cierren)
//**EXPAND_DOLLAR -> Expande la variable $ y la reemplaza siempre qque exista ya alojada en env
//****FT_REPLACE_VAR -> Trocea la string, y copia en la nueva var_real cacho pre + variable desde env  + cacho post
//**FT_SUBSTR_STRJOIN -> saca un cacho y lo junta a la real_var actual

/*1. BUSCAR mayus/minus/_/"" y avanza
     2. Busca = y para
     3. empieza la VARIABLE, fin en espacio o fin de comillas
    ///
     Realloc env
     Copy env
     strdup VAR en ultimo char*
     free env
     return new_env
     */
	//NO FUNCIONA: export a=$USER'$USER'


char *expand_dollar(t_shell *shell, char *str, int *i)
{
	int a;
	char *expanded;
	char *dollar_var;
	int	start;

	start = *i;
	a = -1;
	*i += 1;
	while(str[*i] && str[*i] != ' ' && str[*i] != 34 && str[*i] != '$') //len de la variable
		*i += 1;
	dollar_var = ft_substr(str, start + 1, *i - start - 1); // dollar_var = variable
	while (shell->my_env->env[0][++a]) //buscarla en env
	{
		if (!ft_strncmp(shell->my_env->env[a], dollar_var, ft_strlen(dollar_var)))
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
		exit(1);
	expanded[0] = '\0';
	return (expanded);
}

void	ft_replace_var(char **str, int start, int len, char *replace)
{
	int i;
	char *temp;
	int total_len;

	i = -1;
	total_len = ft_strlen(*str) - len + ft_strlen(replace);
	temp = (char *)ft_calloc(sizeof(char), total_len + 1);
	if (!temp)
		exit(1);
	ft_strlcpy(temp, *str, start + 1);
	ft_strlcat(temp, replace, ft_strlen(replace) + ft_strlen(temp) + 1);
	ft_strlcat(temp, *str + start + len, total_len + 1);
	free(*str);
	*str = NULL;
	*str = ft_strdup(temp);
	free(temp);
	
}

char *ft_substr_strjoin(char *to_sub, char *to_join, int start, int end)
{
    char    *real_temp;
    char    *temp;

    temp = ft_substr(to_sub, start, end - start);
    if (!to_join)
        real_temp  = ft_strdup(temp);
    else
    {
        real_temp = ft_strjoin(to_join, temp);
        free(to_join);
    }
    free(temp);
    return (real_temp);
}

void    *decode_quotes(t_shell *shell, char *dest, char **str, int *i) 
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
			ft_replace_var(str, dollar_pos, *i - dollar_pos, dollar_var);
			*i = dollar_pos + ft_strlen(dollar_var) - 1;
		}
		*i += 1;
	}
	return (ft_substr_strjoin(*str, dest,  start, *i));
}

static  void fill_quote_dollar(char **var, t_shell *shell)
{
	int a;
	int	i;
	int start;
    int     dollar_pos;
	char	*dollar_var;

	
	a = -1;
	while(var[++a])
	{
		i = -1;
		while(var[a][++i])
		{
			if (var[a][i] == 34 || var[a][i] == 39)
			{
				shell->my_env->var_real[a] = decode_quotes(shell, shell->my_env->var_real[a], &var[a], &i);
				i--;
			}
			else if (var[a][i] == '$')
			{
				dollar_pos = i;
				dollar_var = expand_dollar(shell, var[a], &i); 
				ft_replace_var(&var[a], dollar_pos, i - dollar_pos, dollar_var);
				i = dollar_pos - 1;
			}
			else
			{
				start = i;
				while (var[a][i] && var[a][i] != 34 && var[a][i] != 39 && var[a][i] != '$')
					i++;
				shell->my_env->var_real[a] = ft_substr_strjoin(shell->my_env->var[a], shell->my_env->var_real[a], start, i);
				i--;
			}
		}
	}
	shell->my_env->var_real[a] = NULL;
}

static void filter_variables(char **s, t_shell *shell)
{
	int     i;
	int		start;
	int		a;
	int		nbr_var;

	nbr_var = -1;
	a = 0;
    while (s[++a])
    {
    	i = -1;
		start = ++i;
		if (ft_isalpha(s[a][i]) || s[a][i] == '_' || s[a][i] == 34 || s[a][i] == 39)
		{
			while (s[a][++i] && s[a][i] != '=' && (ft_isalpha(s[a][i])
						|| s[a][i] == '_' || s[a][i] == 34 || s[a][i] == 39))
				check_quotes(s[a], &i);
			if (s[a][i] == '=')
			{
				while (s[a][++i] && s[a][i] != ' ')
					check_quotes(s[a], &i);
				shell->my_env->var[++nbr_var] = ft_substr(s[a], start, i - start);
			}
		}
    }
	 shell->my_env->var[++nbr_var] = NULL;
}

void	get_real_vars(t_shell *shell, char *builtin)
{
	char	**builtin_split;
   /*SPLIT*/
	builtin_split = ft_split_2(builtin, ' ', &shell->my_env->nbr_var); 

	/*FILTRO VARIABLES*/
   shell->my_env->var = (char **)ft_calloc(sizeof(char *), (shell->my_env->nbr_var + 1));
   if (!shell->my_env->var)
	   exit(1);
   filter_variables(builtin_split, shell);

   /*INTERPRETAT COMILLAS Y DOLLAR*/
   shell->my_env->nbr_var = 0;
   while (shell->my_env->var[shell->my_env->nbr_var])//contar cuantas no son null
	   shell->my_env->nbr_var++;
   shell->my_env->var_real = (char **)ft_calloc(sizeof(char *), shell->my_env->nbr_var + 1);
   if (!shell->my_env->var_real)
       exit(1);
	fill_quote_dollar(shell->my_env->var, shell);

	/*PRINT*/
	int	a = -1;
	while (shell->my_env->var_real[++a])
 		//continue;
		printf("real_value == %s\n", shell->my_env->var_real[a]);// print, pero es CONTINUE
}

