/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mom_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:35:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/19 21:01:09 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	find_equal_char(char **s, t_shell *shell)
{
	int	i;
	int	a;

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
			shell->my_env->var_real[++shell->my_env->nbr_var]
				= ft_substr(s[a], 0, ft_strlen(s[a]));
	}
	shell->my_env->var_real[++shell->my_env->nbr_var] = NULL;
}

void	get_real_vars(t_shell *shell, char **command_split,
		int nbr_command_split, int replace)
{
	int	a;

	shell->my_env->var_real = (char **)ft_calloc(sizeof(char *),
			nbr_command_split);
	if (!shell->my_env->var_real)
		status_error(strerror(errno), errno);
	if (replace == 1)
		find_equal_char(command_split, shell);
	else
	{
		a = -1;
		while (command_split[++a])
			shell->my_env->var_real[a] = ft_strdup(command_split[a]);
		shell->my_env->var_real[a] = NULL;
	}
}

void	exit_builtin(char **command_split, int nbr_command)
{
	int	i;

	i = -1;
	printf("exit\n");
	if (nbr_command > 2)
	{
		while (command_split[0][++i])
		{
			if (!ft_isdigit(command_split[0][i]))
				status_error("Numeric argument required", 127);
		}
		ft_putstr_fd("Pink peanuts: too many arguments\n", 2);
	}
	else if (nbr_command == 2)
		exit(ft_atoi(command_split[0]));
	else
		exit(0);
}

void	change_enviroment(t_shell **shell, char **var,
		int nbr_command, int replace)
{
	get_real_vars(*shell, var, nbr_command, replace);
	create_lists(*shell);
	replace_env((*shell), replace);
	(*shell)->my_env->env = convert_list_array(*shell);
	get_new_paths((*shell)->my_env->env, *shell);
}

void	check_builtins_mother(t_shell **shell, int id)
{
	char	**new_vars;

	if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "export")
		&& (*shell)->my_pro->child[id].nbr_command > 1)
		change_enviroment(shell, &(*shell)->my_pro->child[id].command_split[1],
			(*shell)->my_pro->child[id].nbr_command, 1);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "unset"))
		change_enviroment(shell, &(*shell)->my_pro->child[id].command_split[1],
			(*shell)->my_pro->child[id].nbr_command, 0);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "cd"))
	{
		new_vars = (char **)ft_calloc(sizeof(char *), 3);
		if (!new_vars)
			status_error(strerror(errno), errno);
		new_vars = cd_builtin((*shell)->my_env->env,
				(*shell)->my_pro->child[id].command_split[1], new_vars);
		if (!new_vars)
			return ;
		change_enviroment(shell, new_vars, 3, 1);
	}
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "exit"))
		exit_builtin(&(*shell)->my_pro->child[id].command_split[1],
			(*shell)->my_pro->child[id].nbr_command);
}
