/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:30:38 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/29 17:48:19 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//INPUT -> Del input [shell->line] determina n* procesos [shell->my_pro->nprocess]y splitea line en [shell->my_pro->orders]
//ALLOC_PROCESS -> aloja array de pipes, crea pipes y aloja array de pids de procesos.
//CREATE PROCESSES -> Fork * nprocess -> redirige cada uno a EXE_COMMAND (exe.c)

#include "../include/minishell.h"


//CREATE PROCESSES//

void create_processes(t_shell *shell)
{
    int i;
	int status;
	//int state;

    i = 0;

    //printf("nbr_proccess = %d\n", shell->my_pro->nprocess);
    while (i < shell->my_pro->nprocess)
    {
        shell->my_pro->pid[i] = fork();
        if (shell->my_pro->pid[i] < 0)
            perror("Error");
        if (shell->my_pro->pid[i] == 0)
			exe_command(shell->my_pro->orders[i], shell, i);
        i++;
    }
	close_pipes(shell);//Hay que cerrar todas las pipes(bucle)
	i = -1;
	while (shell->my_pro->pid[++i])
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
    npipes = (shell->my_pro->nprocess + 1);
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
    shell->my_pro->pid = (int *)malloc(shell->my_pro->nprocess * sizeof (int)); //alojo array de hijos
    if (shell->my_pro->pid < 0)
        exit(1);
//	freees?
	//printf("Alloc Processes OK\n");
}

//INPUT STRING//
//Gestionar comillas primero: las comillas ignoran lo que hay dentro como comando, se convierten en string(parametro) de lo que funcione como comando fuera de ellas. Si hay una pipe dentro puede influir en el split. Igual con los (><)
// Gestionar tambien && y ; ???


int input(t_shell *shell)
{
    int i;

	//printf("Input: %s\n", shell->line);
	shell->my_pro->nprocess = 1;//OJO! si no hay pipes tiene que crear un proceso tambien, por lo que empieza en 1: se puede inicializar en init 
    if (shell->line[0] == '|') //  -Que no nos hayan metido 2 || seguidos
    {
        printf("Error argumentos\n");
        exit (1);
    }
	//comillas
	i = -1;
    while (shell->line[++i]) //  -Contar cuantos procesos
    {
        if (shell->line[i] == '|')
        {
            shell->my_pro->nprocess++;
            if (shell->line[i + 1] == '|') //  -Que no nos hayan metido 2 || seguidos
            {
                printf("Error argumentos\n");
                exit (1);
            }
        }
    }
    //printf("nbr_proccess = %d\n", shell->my_pro->nprocess);
    shell->my_pro->orders = ft_split(shell->line, '|'); //split del input con pipes
    if (shell->my_pro->orders[0] == NULL) //si metes enter hace exit. NOOOO!
    {
        printf("Error argumentos\n");
        exit (1);
    }
    alloc_processes(shell);
    create_processes(shell);
    return (0);
}


