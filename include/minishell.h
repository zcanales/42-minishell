/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:25 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/03 16:49:06 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/libft.h"
#include <unistd.h>
#include <termios.h> /*struct termios*/
#include <stdlib.h>
#include <stdio.h>

typedef struct s_ch //NO ME DEJA CREAR ESTA ESTRUCTURA DENTRO DE T_PRO PRO ???
{
    int     nchild;
    char    **command;
	//char *infile;
	//char *outfile;
}   t_ch;

typedef struct s_pro
{
	int 	nprocess;
    int     *pid;
    int     **fd;
    char    **orders; //he cambiado commands por orders, que es todo el churro entre pipes. Luego el child lo splitea en comands, que es comando + flags
	//t_ch	*child;
    int     nchild;
    char    **command;
	char *infile;//no es array porque omite pero no los modifica
    char **outfile;//es array porque bash los crea aunque los omita.
    int *infile_fd;//
    int **outfile_fd;//los fd de los archivos
}   t_pro;

typedef struct s_env
{
    char    **env;
    char    **paths;
 //   char    *home;
   // char    *root;
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
void    attributes();

/*PROCESSES*/
int input(t_shell *shell);
void alloc_processes(t_shell *shell);
void is_redirected(t_shell *shell);
void create_processes(t_shell *shell);

/*EXE*/
void exe_command(char *order, t_shell *shell, int child);
void re_in_out(t_shell *shell);
void re_pipe(t_shell *shell);

/*UTILS*/
void close_pipes(t_shell *shell);

/*	BUILTINS	*/

/* FT_SLIPT_2 */
char    **ft_split_2(char const *s, char c);
//////LIBERAR MEMORIA: ////
/*shell->my_env->paths[i];(bucle)
shell->my_pro->pid;
shell->my_pro->fd;(bucle)
shell->my_pro->orders;(bucle)
shell->my_pro->child->command;(bucle)*/

#endif
