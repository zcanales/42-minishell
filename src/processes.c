/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:30:38 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/03 20:34:14 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//INPUT -> Del input [shell->line] determina n* procesos [shell->my_pro->nbr_process]y splitea line en [shell->my_pro->orders]
//ALLOC_PROCESS -> aloja array de pipes, crea pipes y aloja array de pids de procesos.
//CREATE PROCESSES -> Fork * nbr_process -> redirige cada uno a EXE_COMMAND (exe.c)

#include "../include/minishell.h"


//CREATE PROCESSES//

void create_processes(t_shell *shell)
{
    int i;
	int status;

    i = -1;
    while (++i < shell->my_pro->nbr_process)
    {
        shell->my_pro->pid[i] = fork();
        if (shell->my_pro->pid[i] < 0)
            perror("Error");
        if (shell->my_pro->pid[i] == 0)
		{
			shell->my_pro->nchild = i;
		//	shell->my_pro->child->id_child = i;
			exe_command(shell->my_pro->orders[i], shell);//ejecucion de child (archivo exe.c)
		}
    }
	close_pipes(shell);//Hay que cerrar todas las pipes(bucle)
	i = -1;
    while (++i < shell->my_pro->nbr_process)
		waitpid(shell->my_pro->pid[i], &status, 0);
	/*if (WIFEXITED(status))
		state = WEXITSTATUS(status);*/
	//printf("Process OK\n");
	return ;
}

//ALLOC PROCESSES//

void alloc_processes(t_shell *shell)
{
    int i;
    int npipes;

    i = -1;
    npipes = (shell->my_pro->nbr_process + 1);
    shell->my_pro->fd = (int **)malloc(npipes * sizeof(int *)); //alojo array de pipes
    if (!shell->my_pro->fd)
        exit(1);
    while (++i < npipes)
    {
        shell->my_pro->fd[i] = (int *)malloc(2 * sizeof(int)); //alojo cada pipe
        if (!shell->my_pro->fd[i])
            exit(1);
        if (pipe(shell->my_pro->fd[i]) < 0)      //creo la pipe
        {
            printf("Error pipe\n");
            exit(1);
        }
    }
    i = 0;
    shell->my_pro->pid = (int *)malloc(shell->my_pro->nbr_process * sizeof (int)); //alojo array de hijos
    if (shell->my_pro->pid < 0)
        exit(1);
//	freees?
//	printf("Alloc Processes OK\n");
}

//INPUT STRING//
//Gestionar comillas primero: las comillas ignoran lo que hay dentro como comando, se convierten en string(parametro) de lo que funcione como comando fuera de ellas. Si hay una pipe dentro puede influir en el split. Igual con los (><)
// Gestionar tambien && y ; ???


int input(t_shell *shell)
{
    int i;

    if (shell->line[0] == '|') //  -Que no nos hayan metido solo |
        exit (1);
    shell->my_pro->orders = ft_split_2(shell->line, '|', &shell->my_pro->nbr_process); //split del input con pipes
	i = -1;
	while (shell->my_pro->orders[++i])
		printf("%d = %s\n", i, shell->my_pro->orders[i]);
    alloc_processes(shell);
   // is_redirected(shell);//Filtro redirecciones, (archivo exe.c)//
    create_processes(shell);
    return (0);
}


