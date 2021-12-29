/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/29 17:48:14 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//EXE_COMMAND -> ejecuta comando. Necesita comando completo con flags o param, struct t_pro *proc (para las redirecciones), y env
//*RE_PIPE -> Redirige canal de in/out. Lee de fd[child][0] en vez de STDIN y escribe en fd[child + 1][1] en vez de STDOUT
//*RE_IN_OUT -> si hay redirecciones infile y outfile. Cuantas posibles? 


#include "../include/minishell.h"

//EXE//

void exe_command(char *order, t_shell *shell, int child) 
{
    int     i;
    char    *temp_access;
    char    *reading;
//	char **command;//todo en la struct, mas comodo pero las lineas son larguisimas

    i = 0;
	reading = NULL;
	shell->my_pro->nchild = child; //no me deja hacerlo en una sub-estructura 
	//re_in_out(shell); //todos pasan por aqui? mirar redireccions posibles
	///OJO! Y si el comando es ./ ????
    shell->my_pro->command = ft_split(order, ' ');
	//printf("Hijo %d - command : %s\n", shell->my_pro->nchild, shell->my_pro->command[0]);
    while (shell->my_env->paths[i])
    {
        temp_access = ft_strjoin(shell->my_env->paths[i], shell->my_pro->command[0]);
        if (!access(temp_access, X_OK))
        {
			re_pipe(shell);
			if (execve(ft_strjoin(shell->my_env->paths[i], shell->my_pro->command[0]), shell->my_pro->command, shell->my_env->env) < 0)
				perror("Error: \n");//funcion errores
        }
        free(temp_access);
        i++;
    }
	exit(0);
}


//RE_PIPE// 

void re_pipe(t_shell *shell)
{
	dup2(shell->my_pro->fd[shell->my_pro->nchild][0], 0);
	if (shell->my_pro->nchild != shell->my_pro->nprocess - 1)
		dup2(shell->my_pro->fd[shell->my_pro->nchild + 1][1], 1);
	close_pipes(shell);  //Hay que cerrar todas las pipes(bucle)
}

/*RE_IN_OUT : Sin adaptar. 
void re_in_out()
{
    com->fd[0][0] = open(argv[1], O_RDONLY);
    if (com->fd[0][0] < 0)
        ft_free_paths(com);
    com->fd[com->nchild][1] = open(argv[argc - 1],
            O_RDWR | O_TRUNC | O_CREAT, 0755);
    if (com->fd[com->nchild][1] < 0)
        exit(1);
}*/


