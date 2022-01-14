/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:26:41 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/14 20:08:34 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_builtins_child(t_shell **shell, int id)
{
	int i;

	if (!ft_strncmp((*shell)->my_pro->child[id].command_split[0], "export", ft_strlen("export")))
	{
		//printf("Soy el hijo tengo export --> MUERO\n");
		exit(0);
	}
	if (!ft_strncmp((*shell)->my_pro->child[id].command_split[0], "env", ft_strlen("env")) && !(*shell)->my_pro->child[id].command_split[0][3])
	{
		i = -1;
		while ((*shell)->my_env->env[++i])
			printf("%s\n", (*shell)->my_env->env[i]);
		exit(0);
	}
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "unset"))
		exit(0);
}
