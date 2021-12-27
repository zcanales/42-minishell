
//GET_ENV -> consigue el env y las paths (alojadas en struct t_env)
//INPUT -> lee del pipeline y guarda la string. Numero de procesos y splitea la string en procesos. 
//*ALLOC_PROCESS -> aloja array de pipes, crea pipes y aloja array de pids de procesos. Necesita saber [proc->nprocess]
//*RE_IN_OUT -> si hay redirecciones 
//EXE_COMMAND -> ejecuta comando. Necesita comando completo con flags o param, struct t_pro *proc (para las redirecciones), y env



//* Para llegar a este punto necesito haber determinado cuantos procesos vamos a hacer (t_pro *proc->nprocess) ( | ) y si entre ellos hay redireccciones ( > < ) 
// ( | ) si hay mas de un proceso -> ALLOC_PROCESS y habilitar redireccion en EXE_COMMAND
// ( < > ) Si hay redirecciones a file necesitamos la funcion RE_IN_OUT


#include "../include/minishell.h"

//INPUT STRING//

int input(t_shell *shell)
{
    int i;

	//Comprobrar:
	//	-En la primera posición no haya un |
	//	-Que no nos hayan metido 2 || seguidos
	//	-Contar cuantos procesos
	if (shell->line[0] == '|')
	{
		printf("Error argumentos\n");
		exit (1);
	}
	i = -1;
	while (shell->line[++i])
	{
		if (shell->line[i] == '|')
		{
			shell->my_pro->nprocess++;
			if (shell->line[i + 1] == '|')
			{
				printf("Error argumentos\n");
				exit (1);
			}
		}
	}
	shell->my_pro->nprocess++;
	printf("nbr_proccess = %d\n", shell->my_pro->nprocess);
  	shell->my_pro->commands = ft_split(shell->line, '|');
	printf("proccess = %s\n", shell->my_pro->commands[0]);
	//split del input con pipes. OJO! SI hubiera una unica pipe! // gestionar tambien && y ; ???
	if (shell->my_pro->commands[0] == NULL)
	{
		printf("Error argumentos\n");
		exit (1);
	}
	alloc_process(shell);
	return (0);
    //hay redirecciones??? toda esta info tiene que llegar a las siguentes
}


//ALLOC PROCESSES//

void alloc_process(t_shell *shell)
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
    //freees?
}
/*
//EXE//

void exe_command(char *order, t_pro *proc, t_env *env) 
{
    int     i;
    char    *temp_access;
	char **command;

    i = 0;
	//Mirar que el 1. commanado no tengo piquito?
    command = ft_split(order, ' ');
    while (env->paths[i])
    {
        temp_access = ft_strjoin(env->paths[i], command[0]);
        if (!access(temp_access, X_OK))
        {
			//Comprobar
			//	1. Redirigir
			//	2. Que se el sea el ultimo hijo: Stdout o file (>)
            //if(proc->nchild == ncprocess) //si soy el ultimo hijo
				//dup2(com->fd[child][0], 0);
            	//dup2(com->fd[child + 1][1], 1);
            	//ft_close(com);
            if (execve(ft_strjoin(env->env_paths[i], command[0]), command, env->env) < 0)
				error();//funcion errores
        }
        free(temp_access);
        free(my_env->paths[i]);
        i++;
    }
}
*/

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


//
