/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:26:41 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/18 17:44:59 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	pwd_builtin(t_shell *shell, char **env)
{
    char   path[1024];
	(void)shell;
	(void)env;
    printf("%s\n", getcwd(path, 1024));
	exit(0) ;
}

void	echo_builtin(char **command_split)
{
	int i;

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
	while(command_split[++i])
	{
		printf("%s", command_split[i]);
		if (command_split[i + 1])
			printf(" ");
		else if (!ft_strcmp(command_split[1], "-n") && !command_split[i + 1])
			printf("\n");
	}
	exit (0);
}

void env_builtin(char **env, int nbr_command, char **command_split)
{
	int i;
	(void)command_split;
	if (nbr_command > 1)
		status_error("Pink: env %s No such file or directory\n", 127);
	//	printf("Pink: : env %s No such file or directory\n", command_split[1]);
	else
	{
		i = -1;
		while (env[++i])
			printf("%s\n",env[i]);
	}
	exit(0);
}

void	check_builtins_child(t_shell **shell, int id)
{
	if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "export"))
		exit(0);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "env"))
		env_builtin((*shell)->my_env->env, (*shell)->my_pro->child[id].nbr_command, &(*shell)->my_pro->child[id].command_split[0]); 
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "unset"))
		exit(0);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "cd"))
		exit(0);
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "pwd"))
		pwd_builtin((*shell), (*shell)->my_env->env); 
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "echo"))
		echo_builtin((*shell)->my_pro->child[id].command_split); 
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "exit"))
	{
		//si es child->id > 1 ->>> Command not found
		//si es child->id 1  && nbr_process > 1 ->>> no hace nada, hijo muere
		//si es child->id 1  && nbr_process = 1 ->>> exit programa(madre)
		printf("Soy un hijo me voy\n");
		exit(0);
	}
}
