/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mom_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:35:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/21 20:51:12 by zcanales         ###   ########.fr       */
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
		while (s[a][i] && s[a][i] != '=' )
		{
			if (!ft_isalnum(s[a][i]) && s[a][i] != '_')
			{
				printf_error(s[a], 1, shell);
				break ;
			}
			i++;
		}
		if (s[a][i] && s[a][i] == '=') 
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
	if (replace != 0)
		find_equal_char(command_split, shell);
	else
	{
		a = -1;
		while (command_split[++a])
			shell->my_env->var_real[a] = ft_strdup(command_split[a]);
		shell->my_env->var_real[a] = NULL;
	}
}

static void	exit_builtin(char **command_split, int nbr_command, t_shell *shell, int id)
{
	int	i;

	i = -1;
	printf("exit\n");
	shell->my_pro->child[id].mom_builtin = 1;
	if (nbr_command > 2)
	{
		while (command_split[0][++i])
		{
			if (!ft_isdigit(command_split[0][i]))
				status_error("Numeric argument required", 127);
		}
		printf_error("", 3, shell);
		shell->status_builtin = 1;
	}
	else if (nbr_command == 2)
		exit(ft_atoi(command_split[0]));
	else
		exit(0);
}

static void	change_enviroment(t_shell **shell, char **var,
		int id, int replace)
{
	if (replace == 2)
		get_real_vars(*shell, var, 3, replace);
	else
		get_real_vars(*shell, var, (*shell)->my_pro->child[id].nbr_command, replace);
	(*shell)->my_pro->child[id].mom_builtin = 1;
	create_lists(*shell, replace);
	if ((*shell)->my_pro->nbr_process == 1)
	{
		replace_env((*shell), replace);
		(*shell)->my_env->env = convert_list_array(shell);
		get_new_paths((*shell)->my_env->env, *shell);
		ft_freelist(&(*shell)->my_env->list_var_real);
	}
	free_double((*shell)->my_env->var_real, 2);
}

void	check_builtins_mother(t_shell **shell, int id)
{
	char	**new_vars;
	
	if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "export")
		&& (*shell)->my_pro->child[id].nbr_command > 1)
		change_enviroment(shell, &(*shell)->my_pro->child[id].command_split[1], id, 1);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "unset"))
		change_enviroment(shell, &(*shell)->my_pro->child[id].command_split[1], id, 0);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "cd"))
	{
		(*shell)->my_pro->child[id].mom_builtin = 1;
		new_vars = (char **)ft_calloc(sizeof(char *), 3);
		if (!new_vars)
			status_error(strerror(errno), errno);
		new_vars = cd_builtin((*shell)->my_env->env,
				&(*shell)->my_pro->child[id].command_split[1], new_vars, (*shell));
		if (!new_vars)
			return ;
		change_enviroment(shell, new_vars, id, 2);
		free_double(new_vars, 2);
	}
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "exit"))
		exit_builtin(&(*shell)->my_pro->child[id].command_split[1],
			(*shell)->my_pro->child[id].nbr_command, *shell, id);
}
