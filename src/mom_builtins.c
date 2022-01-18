/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mom_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:35:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/18 20:06:53 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//SORT_BUILTINGS- export - unset - cd - pwd - echo
//REALLOC_ENV
//ALLOC_NEW_VARS

#include "../include/minishell.h"
#include <string.h>

////////////////////VARS/////////////////////////////////////////////////////////////////////////////////////////


static void find_equal_char(char **s, t_shell *shell)
{
	int     i;
	int		a;

	shell->my_env->nbr_var = -1;
	a = -1;
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

	shell->my_env->var_real = (char **)ft_calloc(sizeof(char *), nbr_command_split);
	if (!shell->my_env->var_real)
		status_error(strerror(errno), errno);
	if (replace == 1)//Busca un '=' Si eres EXPORT
		  find_equal_char(command_split, shell);
	else //copia tal cual todas menos la primera
	{
		a = -1;
		while(command_split[++a])
			shell->my_env->var_real[a] = ft_strdup(command_split[a]);
		shell->my_env->var_real[a] = NULL; 
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
		if (!shell->my_env->paths)
			status_error(strerror(errno), errno);
	}
}
//////////////////CD///////////////////////////


char *special_paths(char **env, char *command_split)
{
	int a;
	char *temp;
	char *find;
	
    if (ft_strcmp(command_split, "-"))
		find = "OLD_PWD=";
	else if (command_split[0] == '~')
		find = "HOME=";
	else
		return (command_split);
	a = -1;
    while (env[++a])
    {
		if (!ft_strncmp(env[a], find, ft_strlen(find)))
        {
			if (command_split[0] == '~')
				temp = ft_strdup(&command_split[1]);
			else 
				temp = (char *)ft_calloc(1, 1);
            free(command_split);
            command_split = ft_strjoin(ft_strdup(&env[a][ft_strlen(find)]), temp);
			free(temp);
			break ;
		}
	}
	return (command_split);
}

char **cd_builtin(char **env, char *command_split, char **new_vars)
{
	int a;
    char   path[1024];

	new_vars[0] = ft_strjoin("OLD_PWD=", ft_strdup(getcwd(path,  1024)));
	if (!command_split)
	{
   		a = -1;
		while (env[++a])
   		{
       		 if (!ft_strncmp(env[a], "HOME=", ft_strlen("HOME=")))
			 {
				if (chdir(&env[a][5]) != 0)
				{
					ft_putstr_fd("Pink peanuts:", 2);
					ft_putstr_fd(strerror(errno), 2);
					ft_putstr_fd("\n", 2);
					return (NULL);
				}
			 }
        }
    }
	else 
	{
		command_split = special_paths(env, command_split);
		if (command_split[0] == '-')
		{
			ft_putstr_fd("Pink peanuts: OLDPWD not set\n", 2);
			return (NULL);
		}
		if (chdir(command_split) != 0)
		{
			ft_putstr_fd("Pink peanuts:", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (NULL);
		}
	}
	new_vars[1] = ft_strjoin("PWD=", ft_strdup(getcwd(path,  1024)));
	new_vars[2] = NULL;
   return (new_vars);	
}
 ////////////////////EXIT///////////////////////////////////
 /*malloc
 1. shell
 	1.1. my_pro
		1.1.1. pid
		1.1.2. fd
		1.1.3. orders
		1.1.4. ch
			-piquito(out/in)
				-file_name
				-file_name_clean
			-command_group
			-commando_split
	1.2. my_env
		1.2.1. env
		1.2.2. path
		1.2.3. var_real
		1.2.4. list_var_real
		1.2.5. list_env
	1.3. line
*/

void	exit_builtin(char **command_split, int nbr_command)
{
	int i;

	i = -1;
	printf("exit\n");
	if (nbr_command > 2)
	{
		while (command_split[0][++i])
		{
			if (!ft_isdigit(command_split[0][i]))
				status_error("Numeric argument required\n", 127);
		}
		ft_putstr_fd("Pink peanuts: too many arguments\n", 2);
	}
	else
		exit(ft_atoi(command_split[0]));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////77
void	change_enviroment(t_shell **shell, char **var, int nbr_command, int replace)
{
		get_real_vars(*shell, var, nbr_command, replace);
		create_lists(*shell);
		replace_env((*shell), replace);
		(*shell)->my_env->env = convert_list_array(*shell);
		get_new_paths((*shell)->my_env->env, *shell);
}	

void    check_builtins_mother(t_shell **shell, int id)
{
	char **new_vars;

    if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "export"))
		change_enviroment(shell, &(*shell)->my_pro->child[id].command_split[1], (*shell)->my_pro->child[id].nbr_command, 1);
	else  if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "unset"))
		change_enviroment(shell, &(*shell)->my_pro->child[id].command_split[1], (*shell)->my_pro->child[id].nbr_command, 0);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "cd"))
	{
		new_vars = (char **)ft_calloc(sizeof(char *), 3);
		if (!new_vars)
			status_error(strerror(errno), errno);
		new_vars = cd_builtin((*shell)->my_env->env, (*shell)->my_pro->child[id].command_split[1], new_vars);
		if (!new_vars)
			return ;
		change_enviroment(shell,new_vars, 3, 1);
	}
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "exit"))
		exit_builtin(&(*shell)->my_pro->child[id].command_split[1], (*shell)->my_pro->child[id].nbr_command);
}
