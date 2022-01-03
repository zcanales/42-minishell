/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:06:18 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/03 20:34:12 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//EXE_COMMAND -> ejecuta comando. Necesita comando completo con flags o param, struct t_pro *proc (para las redirecciones), y env
//*RE_PIPE -> Redirige canal de in/out. Lee de fd[child][0] en vez de STDIN y escribe en fd[child + 1][1] en vez de STDOUT

//IS_REDIRECTED// Comprueba las redirecciones, crea files y redirige a RE_IN_OUT 
//GET_FILES // Guarda infile(ultimo) y outfiles(array) en struct para que luego IS_REDIRECTED siga (crear files, y RE_IN_OUT)
//*RE_IN_OUT -> Redirige STDIN por infile y STDOUT por la ultima posicion de outfile[]


#include "../include/minishell.h"

//EXE//

void exe_command(char *order, t_shell *shell) 
{
    int     i;
    char    *temp_access;

    i = -1;
	shell->my_pro->child->order = order;
//	printf("id =%d\n", shell->my_pro->nchild); //ID. No me deja hacerlo en una sub-estructura 
	//shell->my_pro->nchild = child; //ID. No me deja hacerlo en una sub-estructura 
	//re_in_out(shell); //todos pasan por aqui? mirar redireccions posibles
	///OJO! Y si el comando es ./ ????
    shell->my_pro->command = ft_split_2(order, ' ', &shell->my_pro->nbr_comm);
    while (shell->my_pro->command[++i])
		printf("id =%d %s\n", shell->my_pro->nchild, shell->my_pro->command[i]);
	i = -1;
    while (shell->my_env->paths[++i])
    {
        temp_access = ft_strjoin(shell->my_env->paths[i], shell->my_pro->command[0]);
        if (!access(temp_access, X_OK))
        {
			re_pipe(shell);
			if (execve(ft_strjoin(shell->my_env->paths[i], shell->my_pro->command[0]), shell->my_pro->command, shell->my_env->env) < 0)
				perror("Error: \n");//funcion errores
        }
        free(temp_access);
    }
	exit(0);
}


//RE_PIPE// 

void re_pipe(t_shell *shell)
{
	dup2(shell->my_pro->fd[shell->my_pro->nchild][0], 0);
	if (shell->my_pro->nchild != shell->my_pro->nbr_process - 1)
		dup2(shell->my_pro->fd[shell->my_pro->nchild + 1][1], 1);
	close_pipes(shell);  //Hay que cerrar todas las pipes(bucle)

/*	//if (anterior hijo NO ha tenido outfile) 
		dup2(shell->my_pro->fd[shell->my_pro->nchild][0], 0);
	if (shell->my_pro->nchild != shell->my_pro->nbr_process - 1)// && !outfile)
		dup2(shell->my_pro->fd[shell->my_pro->nchild + 1][1], 1);
	else if(shell->my_pro->nchild != shell->my_pro->nbr_process - 1)//&& outfile)
		re_in_out(shell);

	close_pipes(shell);  //Hay que cerrar todas las pipes(bucle)*/
}

////////////////////////////////////////
//IS_REDIRECTED//

char *get_files(char *order, t_shell *shell)
{
	char *new_order;
	int i;
	int j;

	new_order = order; //(malloc???)
	//recursividad? strchr encuentra piquito, se vuelve a llamar a si misma para encontrar el siguiente.
    //PROBLEMA: no sabemos si el comando lo pone delante o detras. Depende del puto piquito
    //SOLUCION ÑAPA: Split de todo por espacios??? No me gusta
	while(*order)
	{
		if (strchr(order, '<'))// INFILE ->solo tiene que devolver el ultimo, porque no modifica el resto
		{
			j = 0;
			while (eres espacio -> i++)
			while (!otro piquito -> i++ 
			shell->my_pro->infile = substr(order, i, j);//lo coge
			order += strlen(shell->my_pro->infile);
		}
		if (strchr(order, '>'))//este guarda un array de outfiles, tiene que crearlos
		{
		shell->my_pro->outfile = //avanza en la string desde piquito, (espacio), palabra ;
		order = //corta strlen de piquito + espacio si hay + palabra
		}
		else//es comando 
		{
			new_order = strlcat(new_order, (cacho que lea ASCII) //O JOIN//
		}

		i++;
	}
	return (new_order);
}


//Gestionar << (here_doc) limitador
void is_redirected(t_shell *shell)
{
    if (strchr(shell->my_pro->orders[shell->my_pro->nchild], '<') || strchr(shell->my_pro->orders[shell->my_pro->nchild], '>')) //in/out file en orders[nbr_process]
	{
		shell->my_pro->orders[shell->my_pro->nchild] = get_files(shell->my_pro->orders[shell->my_pro->nchild], shell);
	}
	if (infile || outfile)
	{	
		//create (open) ommited files//or redirect and redirect 
		re_in_out(shell);
	}
}

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

/*void    count_piquitos(t_shell *shell, t_ch *ch, int type_file);
{
    int i;

    i = -1;
    while (++i < ch->order[i])
	{
		if (ch->order[i] == '<')
		{
			if (ch->order[++i] == '<')
				ch->infile++;
		}
		if (ch->order[i] == '<')
			exit(1);
		while (
	}
}*/
