/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:48:17 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/19 13:08:56 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_environment(t_env *my_env, char **env)
{
	char	*path;
	char	*temp;
	int		i;

	i = -1;
	while (env[++i])
		continue ;
	my_env->env = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!my_env->env)
		status_error(strerror(errno), errno);
	i = -1;
	while (env[++i])
		my_env->env[i] = ft_strdup(env[i]);
	my_env->env[i] = NULL;
	path = getenv("PATH");
	my_env->paths = ft_split(path, ':');
	i = 0;
	while (my_env->paths[i])
	{
		temp = ft_strjoin(my_env->paths[i], "/");
		free(my_env->paths[i]);
		my_env->paths[i] = temp;
		i++;
	}
}

void	init(t_shell **shell, char **env)
{
	*shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!(*shell))
		status_error(strerror(errno), errno);
	(*shell)->my_env = (t_env *)ft_calloc(sizeof(t_env), 1);
	(*shell)->my_pro = (t_pro *)ft_calloc(sizeof(t_pro), 1);
	if (!(*shell)->my_env || !(*shell)->my_pro)
		status_error(strerror(errno), errno);
	(*shell)->my_pro->child = (t_ch *)ft_calloc(sizeof(t_ch), 1);
	if (!(*shell)->my_pro->child)
		status_error(strerror(errno), errno);
	get_environment((*shell)->my_env, env);
}
