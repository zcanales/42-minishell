/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:00:08 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/07 21:19:40 by eperaita         ###   ########.fr       */
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

static void ft_export_name(char **s, t_shell *shell)
{
	int     i;
	int		start;
	int		a;

	a = 1;
    while (s[a])
    {
    	i = -1;
		while (s[a][++i])
		{
			start = i;
			if (ft_isalpha(s[a][i]) || s[a][i] == '_')
			{
				while (s[a][++i] && s[a][i] != '=')
        			continue ;
				if (s[a][i] == '\0')
					break ;
				while (s[a][i] && s[a][i] != ' ')
					i++;
				//sustraer comillas "a"=2"3"
				shell->my_env->var[a -1] = ft_substr(s[a], start, i - start);
				break;
			}
			else if (s[a][i] == 34 || s[a][i] == 39)
			{
				check_quotes(s[a], &i);
				if (s[a][i] == '\0')
					break ;
				while (s[a][i] && s[a][i] != ' ')
				{
					i++;
					check_quotes(s[a], &i);
				}
				//sustraer comillas "a"=2"3"
				shell->my_env->var[a -1] = ft_substr(s[a], start, i - start);
				break;
			}
		}
		a++;
    }
}

void	ft_export(t_shell *shell)
{
	shell->my_env->var = (char **)ft_calloc(sizeof(char *), (shell->my_pro->child->nbr_command));
	if (!shell->my_env->var)
		exit(1);
   ft_export_name(shell->my_pro->child->command_real, shell);
   int a = -1;
   while (++a < shell->my_pro->child->nbr_command)
	   printf("value == %s\n", shell->my_env->var[a]);
   exit(0);
}


void	ft_sort_builtins(t_shell *shell)
{
	if (ft_strcmp(shell->my_pro->child->command_real[0], "export"))
		ft_export(shell);
}
