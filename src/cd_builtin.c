/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:12:52 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/21 12:36:28 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//////////////////CD///////////////////////////
static char	*special_paths(char **env, char **command)
{
	int		a;
	char	*temp;
	char	*find;
	char	*to_join;

	if (ft_strcmp(command[0], "-"))
		find = "OLDPWD=";
	else if (command[0][0] == '~')
		find = "HOME=";
	a = -1;
	while (env[++a] && (ft_strcmp(command[0], "-") || command[0][0] == '~'))
	{
		if (!ft_strncmp(env[a], find, ft_strlen(find)))
		{
			if (command[0][0] == '~')
				temp = ft_strdup(&command[0][1]);
			else
				temp = (char *)ft_calloc(1, 1);
			to_join = ft_strdup(&env[a][ft_strlen(find)]);
			ft_free(*command);
			command[0] = ft_strjoin(to_join, temp);
			ft_free(temp);
			ft_free(to_join);
			return (command[0]);
		}
	}
	if (command[0][0] == '~')
	{
		temp = ft_strdup(&command[0][1]);
		ft_free(*command);
		to_join = ft_strdup(getenv("HOME"));
		command[0] = ft_strjoin(to_join, temp);
	}
	return (command[0]);
}

static char	**ft_print_return(int err)
{
	ft_putstr_fd("Pink peanuts:", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

static int	cd_builtin_error(char *command_split, int err)
{
	if (command_split[0] == '-')
	{
		ft_putstr_fd("Pink peanuts: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(command_split) != 0)
	{
		ft_print_return(err);
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

char	**cd_builtin(char **env, char **command_split, char **new_vars)
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
			{
				if (chdir(&env[a][5]) != 0)
					return (ft_print_return(errno));
			}
		}
	}
	else
	{
		command_split[0] = special_paths(env, command_split);
		if (cd_builtin_error(command_split[0], errno))
			return (NULL);
	}
	return (get_new_vars(new_vars, str_path));
}
