/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/05 20:45:30 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//IS_REDIRECTED// Comprueba las redirecciones, prioridades, crea files y redirige a RE_IN_OUT 
//*RE_IN_OUT -> SI HAY INFILE/OUTFILE: Redirige STDIN por infile y STDOUT por la ultima posicion de outfile[]
//RE_PIPE -> Conecta canales de in/out. Lee de fd[child][0] en vez de STDIN y escribe en fd[child + 1][1] en vez de STDOUT
//EXE_COMMAND -> ejecuta comando. 

#include "../include/minishell.h"
#include <fcntl.h>
# include <signal.h>

//IS_REDIRECTED//

void is_redirected(t_pro *pro)
{
    //recorrer array de infiles/outfiles y prioridadeS!!
    if (pro->child->nbr_infile)// IN:abrir here_doc tantas veces necesite
	{
		if (pro->child->infile_t->type == 2)
		{
		/*	if (pro->child->id_child != pro->nbr_process - 1)
                kill(pro->pid[pro->child->id_child + 1], SIGSTOP);*/
			here_doc(pro);
			//kill(pro->pid[pro->child->id_child + 1], SIGCONT)
		}
        re_in_out(pro, 0);
	}
    if (pro->child->nbr_outfile) // OUT:crear los outfiles aunque los omita
        re_in_out(pro, 1);
}

//RE_IN_OUT  

void re_in_out(t_pro *pro, int in_out)
{
	if (in_out == 0) //INFILE
	{
		pro->fd[pro->child->id_child][0] = open(pro->child->infile_t->file_name, O_RDONLY);
    	if (pro->fd[pro->child->id_child][0]< 0)
        	exit(1);
	}
	if (in_out == 1) //OUTFILE
	{
		if(pro->child->outfile_t->type == 1)
			pro->fd[pro->child->id_child + 1][1] = open(pro->child->outfile_t->file_name, O_RDWR | O_TRUNC | O_CREAT, 0755);
		if(pro->child->outfile_t->type == 2)
			pro->fd[pro->child->id_child + 1][1] = open(pro->child->outfile_t->file_name, O_RDWR | O_CREAT | O_APPEND, 0755);
		if (pro->fd[pro->child->id_child + 1][1] < 0)
            exit(1);
	}
}


//RE_PIPE//

void re_pipe(t_shell *shell)
{
	if (shell->my_pro->child->id_child != 0 || (shell->my_pro->child->id_child == 0 && shell->my_pro->child->nbr_infile))
		dup2(shell->my_pro->fd[shell->my_pro->child->id_child][0], 0);
	//else 
		//here doc

    if (shell->my_pro->child->id_child != shell->my_pro->nbr_process - 1)
        dup2(shell->my_pro->fd[shell->my_pro->child->id_child + 1][1], 1);
    else if(shell->my_pro->child->id_child == shell->my_pro->nbr_process - 1 && shell->my_pro->child->nbr_outfile)//el ultimo hijo tambien escribe en la pipe si tiene out
		dup2(shell->my_pro->fd[shell->my_pro->child->id_child + 1][1], 1);
    close_pipes(shell);

    //if (anterior hijo ha tenido outfile) ??? se capa la entrada de lectura
}


//EXE// ejecuta comando

void exe_command(t_shell *shell)
{
    int     i;
    char    *temp_access;

    i = -1;
    while (shell->my_env->paths[++i])
    {
        temp_access = ft_strjoin(shell->my_env->paths[i], shell->my_pro->child->command_real[0]);
        if (!access(temp_access, X_OK))
        {
            if (execve(ft_strjoin(shell->my_env->paths[i], shell->my_pro->child->command_real[0]), shell->my_pro->child->command_real, shell->my_env->env) < 0)
                perror("Error: \n");//funcion errores
        }
        free(temp_access);
    }
    exit(0);
}
