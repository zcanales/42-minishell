/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:25 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/12 21:21:14 by eperaita         ###   ########.fr       */
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
    int     id_child;
	//char	*order;		//NO SE USA
    //char    **command;	// NO SE USA
	int    	nbr_command;

	//para ejecutar
	char	*comando_bueno; //Cambiar nombre (Por my_order por ejemplo) (Se usa en child_info.c)
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
	t_ch	*child;//array de hijos
}   t_pro;

typedef struct s_env
{
    char    **env;
	int 	nbr_env;
    char    **paths;
	char	**var;
	char	**var_real;
	int 	nbr_var;
	t_list	*list_var_real;
	t_list	*list_env;
}t_env;

typedef struct	s_shell
{
	struct termios old;
	struct termios changed;
	char	*line;
	int		mother;
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
void    child_process(t_ch *child, t_shell *shell);
void    mother_process(t_shell *shell);

/*CHILD_INFO*/
void    count_piquitos(int *nbr_file, char c, t_piquito **file_t, char *order);
void    chop_order(t_ch *ch, char *order);
void    chop_file_info(t_ch *ch, char c, char no_c, int *i, char *order);
char	*get_real_command(t_ch *ch, int *i, char *order);
void    get_child_info(t_shell *shell);

/*EXECUTE*/
void exe_command(t_shell *shell, int id);
void re_in_out(t_pro *pro, int in_out, int index, int id);
void re_pipe(t_shell *shell, int id);
void is_redirected(t_pro *pro, int id);
	
	/*UTILS*/
void 	close_pipes(t_shell *shell);
void    check_quotes(char *s, int *index);
void    free_double(char **s);
void    imprimir(t_ch *ch); //QUITAR
void	ft_freelist(t_list **head);

/*	EXPORT	*/
void    get_real_vars(t_shell *shell, char **commnad_real, int nbr_commnad_real);


/*  BUILTINS    */
void    check_builtins_child(t_shell **shell, int id);
void    check_builtins_mother(t_shell **shell, int id);

/* FT_SLIPT_2 */
char    **ft_split_2(char const *s, char c, int *nbr_array);

/*HERE_DOC*/
void here_doc(t_pro *pro, int index, int id);

/*ERRORS */
void    check_error( char *line);
void    check_error_pipe(char **orders);

//////LIBERAR MEMORIA: ////
/*shell->my_env->paths[i];(bucle)
shell->my_pro->pid;
shell->my_pro->fd;(bucle)
shell->my_pro->orders;(bucle)
shell->my_pro->child->command;(bucle)*/

/////////NOTAS////////
//Cambiar nombre de piquito (ingles)

#endif
