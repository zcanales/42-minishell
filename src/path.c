/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:26:20 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/24 11:52:36 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//GET_NEW_PATHS -> Cd builtin. Resets $PATH in env 
	//GET_NEW_PATHS_ELSE -> Aux function 
//GET_EXE_PATH -> ./ must go to execvue as command[0]
//SPECIAL_PATHS -> If the path is back or home

//////////////SPECIAL PATHS/////////////////
static char	*special_paths_back(char **env, char **command, char *find)
{
	int		a;
	char	*temp;
	char	*to_join;

	temp = NULL;
	a = -1;
	while (env[++a])
	{
		if (!ft_strncmp(env[a], find, ft_strlen(find)))
		{
			if (command[0][0] == '~')
				temp = ft_strdup(&command[0][1]);
			else if (command[0][0] == '-')
				temp = (char *)ft_calloc(1, 1);
			to_join = ft_strdup(&env[a][ft_strlen(find)]);
			ft_free(*command);
			command[0] = ft_strjoin(to_join, temp);
			ft_free(temp);
			ft_free(to_join);
			return (command[0]);
		}
	}
	return (command[0]);
}

char	*special_paths(char **env, char **command)
{
	char	*temp;
	char	*to_join;

	if (ft_strcmp(command[0], "-"))
		return (special_paths_back(env, command, "OLDPWD="));
	else if (command[0][0] == '~')
		command[0] = special_paths_back(env, command, "HOME=");
	if (command[0][0] == '~')
	{
		temp = ft_strdup(&command[0][1]);
		ft_free(*command);
		to_join = ft_strdup(getenv("HOME"));
		command[0] = ft_strjoin(to_join, temp);
	}
	return (command[0]);
}

///////////////// -  "./" -  //////////////////
char	*get_exe_path(t_shell *shell, char *command_split)
{
	char	*new_command;

	new_command = NULL;
	free_double(shell->my_env->paths, 2);
	shell->my_env->paths = (char **)ft_calloc(sizeof(char *), 2);
	if (!shell->my_env->paths)
		status_error(strerror(errno), errno);
	shell->my_env->paths[0] = ft_substr(command_split, 0,
			ft_strlen(command_split)
			- ft_strlen(ft_strrchr(command_split, '/')) + 1);
	if (ft_strrchr(command_split, '/'))
		new_command = ft_strdup(ft_strrchr(command_split, '/') + 1);
	else
		status_error("Command not found", 127);
	free (command_split);
	return (new_command);
}

////////////////////////PATHS////////////////////
void	get_new_path_else(t_shell *shell)
{
	free_double(shell->my_env->paths, 2);
	shell->my_env->paths = (char **)ft_calloc(sizeof(char *), 1);
	if (!shell->my_env->paths)
		status_error(strerror(errno), errno);
}

void	get_new_paths(char **env, t_shell *sh)
{
	int		a;
	char	*temp;

	a = -1;
	while (env[++a])
	{
		if (!ft_strncmp(env[a], "PATH=", ft_strlen("PATH=")))
		{
			free_double(sh->my_env->paths, 2);
			sh->my_env->paths = ft_split(&env[a][ft_strlen("PATH=" - 1)], ':');
			break ;
		}
	}
	if (env[a] != NULL)
	{
		a = -1;
		while (sh->my_env->paths[++a])
		{
			temp = ft_strjoin(sh->my_env->paths[a], "/");
			free(sh->my_env->paths[a]);
			sh->my_env->paths[a] = temp;
		}
	}
	else
		get_new_path_else(sh);
}
