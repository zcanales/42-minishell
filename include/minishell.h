/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:25 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/04 20:31:32 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/libft.h"
#include <unistd.h>
#include <termios.h> /*struct termios*/
#include <stdlib.h>
#include <stdio.h>

typedef struct s_piquito
{
	int		type;		// simple = 1; double = 2; 
	int 	fd;			//Su fd
	int 	priority;	// 0 - 1
	char	*file_name;
}t_piquito;

typedef struct s_ch 
{
    int     id_child;	//identificardor
	char	*order;		//churro
    char    **command;	//comando bueno se tiene que convertir en eso, un split de espacios. 
	int    	nbr_command;

	//para ejecutar
	char	*comando_bueno;
	char	**command_real;

	//info files
	int		nbr_infile;
	int		nbr_outfile;

	t_piquito	*infile_t;
	t_piquito	*outfile_t;
	int		index_in;
	int		index_out;
}   t_ch;

typedef struct s_pro
{
	int 	nbr_process;
    int     *pid;
    int     **fd;
    char    **orders;
	t_ch	*child;
}   t_pro;

typedef struct s_env
{
    char    **env;
    char    **paths;
}t_env;

typedef struct	s_shell
{
	struct termios old;
	struct termios changed;
	char	*line;
	t_env	*my_env;
	t_pro	*my_pro;

}t_shell;

/*	INIT	*/
void	init(t_shell **shell, char **env);
void get_environment(t_env *my_env, char **env);

/* TERMINAL	*/
int		create_terminal(t_shell *shell);
void    attributes();

/*PROCESSES*/
int input(t_shell *shell);
void alloc_processes(t_shell *shell);
void create_processes(t_shell *shell);
void    child_process(char *order, t_shell *shell);
void    mother_process(t_shell *shell);

/*CHOP_ORDER*/
void    count_piquitos(t_ch *ch, int *nbr_file, char c, t_piquito **file_t);
void    chop_order(t_ch *ch);
void    chop_file_info(t_ch *ch, char c, char no_c, int *i);
char	*get_real_command(t_ch *ch, int *i);

/*EXECUTE*/
void exe_command(t_shell *shell);
void re_in_out(t_shell *shell);
void re_pipe(t_shell *shell);
void is_redirected(t_shell *shell);
	
	/*UTILS*/
void 	close_pipes(t_shell *shell);
void    check_quotes(char *s, int *index);
void    free_double(char **s);
void    imprimir(t_ch *ch); //QUITAR

/*	BUILTINS	*/

/* FT_SLIPT_2 */
char    **ft_split_2(char const *s, char c, int *nbr_array);


//////LIBERAR MEMORIA: ////
/*shell->my_env->paths[i];(bucle)
shell->my_pro->pid;
shell->my_pro->fd;(bucle)
shell->my_pro->orders;(bucle)
shell->my_pro->child->command;(bucle)*/

#endif
