/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:26:41 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/24 14:16:31 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//CHECK_BUILTINS_CHILD -> Filter bultins. If it si a mom builtin (exit)
	//EXIT_BUILTIN__CHILD -> Exit the program and filter exit args
	//ENV_BU -> Env to te STDIN, if has check(), prints declare -x + env[i]
	//ECHO_BUILTIN -> Print args, if has -n without \n
	//PWD_BUILTIN -> Prints $PWD

void	pwd_builtin(void )
{
	char	path[1024];

	printf("%s\n", getcwd(path, 1024));
	exit(0);
}

void	echo_builtin(char **command_split)
{
	int	i;

	if (ft_strcmp(command_split[1], "-n"))
		i = 1;
	else
		i = 0;
	if (!command_split[i + 1])
	{
		if (i == 0)
			printf("\n");
		exit(0);
	}
	while (command_split[++i])
	{
		printf("%s", command_split[i]);
		if (command_split[i + 1])
			printf(" ");
		else if (!ft_strcmp(command_split[1], "-n") && !command_split[i + 1])
			printf("\n");
	}
	exit(0);
}

void	env_bu(char **env, int nbr_command, int check)
{
	int	i;

	if (nbr_command > 1 && check == 0)
		status_error("No such file or directory", 127);
	else
	{
		i = -1;
		while (env[++i])
		{
			if (check == 1)
				printf("declare -x");
			printf("%s\n", env[i]);
		}
	}
	exit(0);
}

void	exit_builtin_child(char **command_split, int nbr_command)
{
	int	i;

	i = -1;
	if (nbr_command > 1)
	{
		while (command_split[0][++i])
		{
			if (!ft_isdigit(command_split[0][i]))
				status_error("Numeric argument required", 255);
		}
	}
	if (nbr_command > 2)
		status_error("Too many arguments", 1);
	else
	{
		if (nbr_command == 2)
			exit(ft_atoi(command_split[0]));
		exit(0);
	}
}

void	check_builtins_child(t_shell **sh, int id)
{
	if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "export"))
	{
		if ((*sh)->my_pro->child[id].nbr_command == 1)
			env_bu((*sh)->my_env->env, (*sh)->my_pro->child[id].nbr_command, 1);
		else
			exit(0);
	}
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "env"))
		env_bu((*sh)->my_env->env, (*sh)->my_pro->child[id].nbr_command, 0);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "unset"))
		exit(0);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "cd"))
		exit(0);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "pwd"))
		pwd_builtin();
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "echo"))
		echo_builtin((*sh)->my_pro->child[id].command_split);
	else if (ft_strcmp((*sh)->my_pro->child[id].command_split[0], "exit"))
	{
		if ((*sh)->my_pro->nbr_process > 1)
			exit_builtin_child(&(*sh)->my_pro->child[id].command_split[1],
				(*sh)->my_pro->child[id].nbr_command);
		else
			exit (1);
	}
}
