/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:48:17 by zcanales          #+#    #+#             */
/*   Updated: 2022/01/04 19:20:52 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//GET_ENV -> consigue el env y las paths (alojadas en struct t_env)
void get_environment(t_env  *my_env, char **env)
{
    char    *path;
    char    *temp;
    int     i;

    my_env->env = env;
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

void init(t_shell **shell, char **env)
{
    *shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
    if (!(*shell))
        exit (1);
    (*shell)->my_env = (t_env *)ft_calloc(sizeof(t_env), 1);
    (*shell)->my_pro = (t_pro *)ft_calloc(sizeof(t_pro), 1);
    if (!(*shell)->my_env || !(*shell)->my_pro)
       exit (1);
	(*shell)->my_pro->child = (t_ch*)ft_calloc(sizeof(t_ch), 1);
    if (!(*shell)->my_pro->child)
        exit (1);
    get_environment((*shell)->my_env, env);
}
