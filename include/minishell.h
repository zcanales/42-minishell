/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:50:40 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/27 14:15:41 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/libft.h"
#include <unistd.h>
#include <termios.h> /*struct termios*/
#include <stdlib.h>
#include <stdio.h>

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
    char    *home;
    char    *root;
}t_env;

typedef struct	s_shell
{
	struct termios old;
	struct termios changed;
	char *line;
	t_env	*my_env;
	t_pro	*my_pro;

}t_shell;

/*	INIT	*/
int	init(t_shell **shell, char **env);
void get_environment(t_env *my_env, char **env);

/* TERMINAL	*/
int		create_terminal(t_shell *shell);
//void	rl_clear_history(void);
void    attributes();

/*PROCESSES*/
int input(t_shell *shell);
void exe_command(char *order, t_pro *proc, t_env *env);
void alloc_process(t_pro *proc);

#endif
