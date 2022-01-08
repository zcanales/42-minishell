/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:00:08 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/08 14:34:07 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
    //La reconoce auto con $VAR????
	//
	//

static char *ft_substr_strjoin(t_shell *shell, int a, int start, int i)
{
    char    *real_temp;
    char    *temp;

    temp = ft_substr(shell->my_env->var[a], start, i - start);
    if (!shell->my_env->var_real[a])
        real_temp  = ft_strdup(temp);
    else
	{
        real_temp = ft_strjoin(shell->my_env->var_real[a], temp);
		free(shell->my_env->var_real[a]);
	}
	free(temp);
    return (real_temp);
}

static void    *decode_quotes(t_shell *shell, int *i, int a)
{
    int     start;
	char	quote;

	quote = shell->my_env->var[a][*i];
	*i += 1;
    start = *i;
    while (shell->my_env->var[a][*i] && shell->my_env->var[a][*i] != quote)
	{
//		if (shell->my_env->var[a][*i] == '$' && shell->my_env->var[a][*i] == 34)
//			expand_dollar(shell, i);
		*i += 1;
	}
	return (ft_substr_strjoin(shell, a, start, *i));
}

static  void get_real_variable(char **var, t_shell *shell)
{
	int a;
	int	i;
	int start;

	a = -1;
	while(var[++a])
	{
		i = -1;
		while(var[a][++i])
		{
			if (var[a][i] == 34 || var[a][i] == 39)
				shell->my_env->var_real[a] = decode_quotes(shell, &i, a);
			else if (var[a][i] == '$')
				i++;
//				expand_dollar(shell, &i);// tambien hace substr_join
			else
			{
				start = i;
				while (var[a][i] && var[a][i] != 34 && var[a][i] != 39 && var[a][i] != '$')
					i++;
				shell->my_env->var_real[a] = ft_substr_strjoin(shell, a, start, i);
				i--;
			}
		}
	}
	shell->my_env->var_real[a] = NULL;
}

static void export_name(char **s, t_shell *shell)
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

void	ft_export(t_shell *shell)
{
   int a;
   
   a = -1;
   shell->my_env->var = (char **)ft_calloc(sizeof(char *), (shell->my_pro->child->nbr_command + 1));
   if (!shell->my_env->var)
	   exit(1);
   export_name(shell->my_pro->child->command_real, shell);
   while (shell->my_env->var[++a])//contar cuantas no son null
	   continue;
	   //printf("value == %s, a= %d\n", shell->my_env->var[a], a);// print, pero es CONTINUE
   shell->my_env->var_real = (char **)ft_calloc(sizeof(char *), a + 1);
   if (!shell->my_env->var_real)
       exit(1);
	get_real_variable(shell->my_env->var, shell);
	a = -1;
	while (shell->my_env->var_real[++a])
 		//continue;
		printf("real_value == %s\n", shell->my_env->var_real[a]);// print, pero es CONTINUE
	//realloc env
	//substr var en env
   exit(0);
}


void	ft_sort_builtins(t_shell *shell)
{
	if (ft_strcmp(shell->my_pro->child->command_real[0], "export"))
		ft_export(shell);
}
