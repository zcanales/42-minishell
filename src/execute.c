/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/17 20:15:31 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//IS_REDIRECTED// Comprueba las redirecciones, prioridades, crea files y redirige a RE_IN_OUT o HERE_DOC 
	//*RE_IN_OUT -> SI HAY INFILE/OUTFILE: Redirige STDIN por infile y STDOUT por la ultima posicion de outfile[]
	//*HERE_DOC -> here_doc.c
//RE_PIPE -> Conecta canales de in/out. Lee de fd[child][0] en vez de STDIN y escribe en fd[child + 1][1] en vez de STDOUT
//EXE_COMMAND -> ejecuta comando. 

#include "../include/minishell.h"
#include <fcntl.h>
# include <signal.h>

//CLOSE PIPES//

void close_pipes(t_shell *shell)
{
	int i;
    int j;
	
	i = 0;
    while (i < shell->my_pro->nbr_process + 1)
    {
        j = 0;
        while (j < 2)
        {
            close(shell->my_pro->fd[i][j]);
            j++;
        }
        i++;
    }
}

//IS_REDIRECTED//

void is_redirected(t_pro *pro, int id)
{
	int i;

	i = -1;
    while (++i <  pro->child[id].nbr_infile)
	{
		if (i == 0)
			unlink("here_doc.txt");
		if (pro->child[id].infile_t[i].type == 2)
		{
			here_doc(pro, i, id);
			if (i != (pro->child[id].nbr_infile - 1))
				unlink("here_doc.txt");
		}
		else
        	re_in_out(pro, 0, i, id);
	}
	i = -1;
    while (++i < pro->child[id].nbr_outfile)         
		re_in_out(pro, 1, i, id);
}

//RE_IN_OUT  

void re_in_out(t_pro *pro, int in_out, int index, int id)
{
	if (in_out == 0) //INFILE
	{
		pro->fd[id][0] = open(pro->child[id].infile_t[index].file_name, O_RDONLY);
    	if (pro->fd[id][0]< 0)
        	exit(1);//no such or deirectory
	}
	if (in_out == 1) //OUTFILE
	{
		if(pro->child[id].outfile_t[index].type == 1)
			pro->fd[id + 1][1] = open(pro->child[id].outfile_t[index].file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if(pro->child[id].outfile_t[index].type == 2)
			pro->fd[id + 1][1] = open(pro->child[id].outfile_t[index].file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (pro->fd[id + 1][1] < 0)
            exit(1);
	}
}


//RE_PIPE//

void re_pipe(t_shell *shell, int id)
{
	if (id != 0 || (id == 0 && shell->my_pro->child[id].nbr_infile))
		dup2(shell->my_pro->fd[id][0], 0);

    if (id != shell->my_pro->nbr_process - 1)
        dup2(shell->my_pro->fd[id + 1][1], 1);
    else if(id  == shell->my_pro->nbr_process - 1 && shell->my_pro->child[id].nbr_outfile)//el ultimo hijo tambien escribe en la pipe si tiene out
		dup2(shell->my_pro->fd[id + 1][1], 1);
    close_pipes(shell);
}


//EXE//

void exe_command(t_shell *shell, int id)
{
    int     i;
    char    *temp_access;

    i = -1;
	if (!shell->my_pro->child[id].command_split[0])
		exit(0);
    while (shell->my_env->paths[++i])
    {
        temp_access = ft_strjoin(shell->my_env->paths[i], shell->my_pro->child[id].command_split[0]);
        if (!access(temp_access, X_OK))
        {
            if ((execve(ft_strjoin(shell->my_env->paths[i], shell->my_pro->child[id].command_split[0]), shell->my_pro->child[id].command_split, shell->my_env->env)) < 0)
                printf("%s", strerror(errno));//funcion errores
        }
        free(temp_access);
    }
	printf("Pink: %s comand not found\n", shell->my_pro->child[id].command_split[0]);
    exit(1);
}
