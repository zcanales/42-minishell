/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:50:40 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/24 17:18:32 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/libft.h"
#include <unistd.h>

typedef struct s_pro
{
	int 	nprocess;
    int     *pid;
    int     **pipe;
    char    **commands;
}   t_pro;

typedef struct s_env
{
    char    **env;
    char    **paths;
}   t_env;

/* TERMINAL	*/
int		create_terminal(void);
//void	rl_clear_history(void);
void    attributes();

/*PROCESSES*/
void get_env(char **env);
static void exe_command(char *order, t_pro *proc, t_env *env)
void alloc_process(t_pro *proc);

#endif
