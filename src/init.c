/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:48:17 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/29 11:39:10 by eperaita         ###   ########.fr       */
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
        //printf("PATH = %s\n", my_env->paths[i]);
        i++;
    }
}

int init(t_shell **shell, char **env)
{
    *shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
    if (!(*shell))
        return (1);
    (*shell)->my_env = (t_env *)ft_calloc(sizeof(t_env), 1);
    (*shell)->my_pro = (t_pro *)ft_calloc(sizeof(t_pro), 1);
    if (!(*shell)->my_env || !(*shell)->my_pro)
        return (1);
    get_environment((*shell)->my_env, env);
    return (0);
}
