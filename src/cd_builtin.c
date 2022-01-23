/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:12:52 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/23 18:39:11 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <dirent.h>

//CD_BUILTING -> Gets the current path and goes to $HOME (if has no arg)
//or to GET_NEW_VARS with the correct path as an arg. 
	//RETURN_ERROR -> Has not found HOME (FT_PRINT_RETURN)
	//GET_NEW_VARS -> Sets new PWD and sends new_vars to MOM_BUILTINGS 
	//CD_BUILTIN_ERROR -> Can't opendir or OLD_PWD not set (FT_PRINT_RETURN)
//FT_PRINT_RETURN -> Prints error and return (no exit) 

static char	**ft_print_return(int err, t_shell *shell)
{
	ft_putstr_fd("Pink peanuts:", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putstr_fd("\n", 2);
	shell->status_builtin = 1;
	return (NULL);
}

static int	cd_builtin_error(char *command_split, int err, t_shell *shell)
{
	if (command_split[0] == '-')
	{
		ft_putstr_fd("Pink peanuts: OLDPWD not set\n", 2);
		shell->status_builtin = 1;
		return (1);
	}
	if (!opendir(command_split) || (shell->my_pro->nbr_process == 1
			&& chdir(command_split) != 0))
	{
		ft_print_return(err, shell);
		return (1);
	}
	return (0);
}

static char	**get_new_vars(char **new_vars, char *str_path)
{
	char	path[1024];

	ft_free(str_path);
	str_path = ft_strdup(getcwd(path, 1024));
	new_vars[1] = ft_strjoin("PWD=", str_path);
	new_vars[2] = NULL;
	ft_free(str_path);
	return (new_vars);
}

static char	**return_error(t_shell *shell, char **env, int a)
{
	if (!opendir(&env[a][5]))
		return (ft_print_return(errno, shell));
	if (shell->my_pro->nbr_process == 1 && chdir(&env[a][5]) != 0)
		return (ft_print_return(errno, shell));
	return (NULL);
}

char	**cd_builtin(char **env, char **command_split,
		char **new_vars, t_shell *shell)
{
	int		a;
	char	path[1024];
	char	*str_path;

	str_path = ft_strdup(getcwd(path, 1024));
	new_vars[0] = ft_strjoin("OLDPWD=", str_path);
	if (!command_split[0])
	{
		a = -1;
		while (env[++a])
		{
			if (!ft_strncmp(env[a], "HOME=", ft_strlen("HOME=")))
				return (return_error(shell, env, a));
		}
	}
	else
	{
		command_split[0] = special_paths(env, command_split);
		if (cd_builtin_error(command_split[0], errno, shell))
			return (NULL);
	}
	return (get_new_vars(new_vars, str_path));
}
