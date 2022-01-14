/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mom_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:35:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/14 20:05:10 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//SORT_BUILTINGS- export - unset - cd - pwd - echo
//REALLOC_ENV
//ALLOC_NEW_VARS

#include "../include/minishell.h"

////////////////////VARS/////////////////////////////////////////////////////////////////////////////////////////


static void find_equal_char(char **s, t_shell *shell)
{
	int     i;
	int		a;

	shell->my_env->nbr_var = -1;
	a = 0;
    while (s[++a])
    {
    	i = 0;
		while (s[a][i] && s[a][i] != '=' && (ft_isalpha(s[a][i])
					|| s[a][i] == '_' || s[a][i] == 34 || s[a][i] == 39 ||
				   	s[a][i] == '$' || ft_isdigit(s[a][i])))
			i++;
		if (s[a][i] == '=')
			shell->my_env->var_real[++shell->my_env->nbr_var] = ft_substr(s[a], 0, ft_strlen(s[a]));
    }
	 shell->my_env->var_real[++shell->my_env->nbr_var] = NULL;
}

void	get_real_vars(t_shell *shell, char **command_split, int nbr_command_split, int replace)
{
	int a;

	shell->my_env->var_real = (char **)ft_calloc(sizeof(char *), nbr_command_split + replace);
	if (!shell->my_env->var_real)
		exit(1);
	if (replace == 1)//Busca un '=' Si eres EXPORT
		  find_equal_char(command_split, shell);
	else //copia tal cual todas menos la primera
	{
		a = 0;
		while(command_split[++a])
			shell->my_env->var_real[a - 1] = ft_strdup(command_split[a]);
		shell->my_env->var_real[a - 1] = NULL; 
	}
}

////////////////////////PATHS////////////////////////////////////////////////////////////////////////////////

void get_new_paths(char **env, t_shell *shell)
{
	int a;
	char *temp;

	a = -1;
	while (env[++a])
	{
		if (!ft_strncmp(env[a], "PATH=", ft_strlen("PATH=")))
		{
			free_double(shell->my_env->paths, 2);
			shell->my_env->paths = ft_split(&env[a][ft_strlen("PATH=" - 1)], ':');
			break;
		}
	}
	if (env[a] != NULL)
	{
		a = -1;
    	while (shell->my_env->paths[++a])
    	{
        	temp = ft_strjoin(shell->my_env->paths[a], "/");
			free(shell->my_env->paths[a]);
        	shell->my_env->paths[a] = temp;
    	}
	}
	else
	{
		free_double(shell->my_env->paths, 2);
		shell->my_env->paths = (char **)ft_calloc(sizeof(char *), 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////77
   
void    check_builtins_mother(t_shell **shell, int id)
{

    if (!ft_strncmp((*shell)->my_pro->child[id].command_split[0], "export", ft_strlen("export")) && !(*shell)->my_pro->child[id].command_split[0][6])
	{
		get_real_vars(*shell, (*shell)->my_pro->child[id].command_split, (*shell)->my_pro->child[id].nbr_command, 1);
		create_lists(*shell);
		replace_env((*shell), 1);
		(*shell)->my_env->env = convert_list_array(*shell);
		get_new_paths((*shell)->my_env->env, *shell);

	}
	else  if (!ft_strncmp((*shell)->my_pro->child[id].command_split[0], "unset", ft_strlen("unset")) && !(*shell)->my_pro->child[id].command_split[0][5])
	{
		//printf("Soy la madre y tengo unset --> %s \n",(*shell)->my_pro->child[id].command_split[0]);
		get_real_vars(*shell, (*shell)->my_pro->child[id].command_split, (*shell)->my_pro->child[id].nbr_command, 0);
		create_lists(*shell);
		replace_env((*shell), 0);
		(*shell)->my_env->env = convert_list_array(*shell);
		get_new_paths((*shell)->my_env->env, *shell);
		
	}
	//aqui irian las dos ultimas lineas que se repiten
}
