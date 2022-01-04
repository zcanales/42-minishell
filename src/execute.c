/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/04 20:31:27 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//IS_REDIRECTED// Comprueba las redirecciones, prioridades, crea files y redirige a RE_IN_OUT 
//*RE_IN_OUT -> SI HAY INFILE/OUTFILE: Redirige STDIN por infile y STDOUT por la ultima posicion de outfile[]
//*RE_PIPE -> Conecta canales de in/out. Lee de fd[child][0] en vez de STDIN y escribe en fd[child + 1][1] en vez de STDOUT
//EXE_COMMAND -> ejecuta comando. 

#include "../include/minishell.h"

//EXE//

void exe_command(t_shell *shell) 
{
    int     i;
    char    *temp_access;

	/*EJECUTAMOS COMANDOS */
	i = -1;
    while (shell->my_env->paths[++i])
    {
        temp_access = ft_strjoin(shell->my_env->paths[i], shell->my_pro->child->command_real[0]);
        if (!access(temp_access, X_OK))
        {
			re_pipe(shell);
			if (execve(ft_strjoin(shell->my_env->paths[i], shell->my_pro->child->command_real[0]), shell->my_pro->child->command_real, shell->my_env->env) < 0)
				perror("Error: \n");//funcion errores
        }
        free(temp_access);
    }
	exit(0);
}


//RE_PIPE// 

void re_pipe(t_shell *shell)
{
	dup2(shell->my_pro->fd[shell->my_pro->child->id_child][0], 0);
	if (shell->my_pro->child->id_child != shell->my_pro->nbr_process - 1)
		dup2(shell->my_pro->fd[shell->my_pro->child->id_child + 1][1], 1);
	close_pipes(shell);  //Hay que cerrar todas las pipes(bucle)

/*	//if (anterior hijo NO ha tenido outfile) 
		dup2(shell->my_pro->fd[shell->my_pro->child->id_child][0], 0);
	if (shell->my_pro->child->id_child != shell->my_pro->nbr_process - 1)// && !outfile)
		dup2(shell->my_pro->fd[shell->my_pro->child->id_child + 1][1], 1);
	else if(shell->my_pro->child->id_child != shell->my_pro->nbr_process - 1)//&& outfile)
		re_in_out(shell);

	close_pipes(shell);  //Hay que cerrar todas las pipes(bucle)*/
}

////////////////////////////////////////
//IS_REDIRECTED//
/*
//Gestionar << (here_doc) limitador
void is_redirected(t_shell *shell)
{
    if (strchr(shell->my_pro->orders[shell->my_pro->child->id_child], '<') || strchr(shell->my_pro->orders[shell->my_pro->child->id_child], '>')) //in/out file en orders[nbr_process]
	{
		shell->my_pro->orders[shell->my_pro->child->id_child] = get_files(shell->my_pro->orders[shell->my_pro->child->id_child], shell);
	}
	if (infile || outfile)
	{	
		//create (open) ommited files//or redirect and redirect 
		re_in_out(shell);
	}
}
*/
//RE_IN_OUT : Sin adaptar. 
//
/*void re_in(t_shell *shell)
{
    com->fd[0][0] = open(infile, O_RDONLY);
    if (com->fd[0][0] < 0)
        exit(1);//ft_free_paths(com);
}
void re_out(t_shell *shell)
{
	while()
	{
		com->fd[nchild + 1][1] = open(oufile[ultimo],
            O_RDWR | O_TRUNC | O_CREAT, 0755);
    	if (com->fd[com->nchild][1] < 0)
        	exit(1);
	}
}*/

