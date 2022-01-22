/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:26:20 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/22 18:19:01 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
