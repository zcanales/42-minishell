
//GET_ENV -> consigue el env y las paths (alojadas en struct t_env)
//INPUT -> lee del pipeline y guarda la string. Numero de procesos y splitea la string en procesos. 
//*ALLOC_PROCESS -> aloja array de pipes, crea pipes y aloja array de pids de procesos. Necesita saber [proc->nprocess]
//*RE_IN_OUT -> si hay redirecciones 
//EXE_COMMAND -> ejecuta comando. Necesita comando completo con flags o param, struct t_pro *proc (para las redirecciones), y env



//* Para llegar a este punto necesito haber determinado cuantos procesos vamos a hacer (t_pro *proc->nprocess) ( | ) y si entre ellos hay redireccciones ( > < ) 
// ( | ) si hay mas de un proceso -> ALLOC_PROCESS y habilitar redireccion en EXE_COMMAND
// ( < > ) Si hay redirecciones a file necesitamos la funcion RE_IN_OUT


//GET ENV//

void get_env(char **env)
{
    t_env   my_env;
    char    *path;
    char    *temp;
    int     i;

    i = 0;
    my_env.env = env;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH", 4))
            path = env[i];
        i++;
    }
    path = path + 5;
    //malloc de cuantas path? para el split?
    my_env.paths = ft_split(path, ':');
    i = 0;
    while (my_env.paths[i])
    {
        temp = ft_strjoin(my_env.paths[i], "/");
        free(my_env.paths[i]);
        my_env.paths[i] = temp;
        i++;
    }
}

//INPUT STRING//

void input()
{
    t_pro proc;
    char *input;
    int i;

    i = 0;
    //leer del pipeline (read?)
    proc.commands = ft_split(input, "|"); //split del input con pipes. OJO! SI hubiera una unica pipe! // gestionar tambien && y ; ???
    while (proc.commands[i++]) //contar cuantos procesos
        proc.nprocess++;
    //hay redirecciones??? toda esta info tiene que llegar a las siguentes
}


//ALLOC PROCESSES//

void alloc_process(t_pro *proc)
{
    int i;
    int npipes;

    i = 0;
    npipes = (proc->nprocess + 1);
    proc->pipe = (int **)malloc(npipes * sizeof(int *)); //alojo array de pipes
    if (!proc->pipe)
            ft_error(com);
    while (i < npipes)
    {
        proc->pipe[i] = (int *)malloc(2 * sizeof(int)); //alojo cada pipe
        if (!proc->pipe[i])
            ft_error(com);
        if (pipe(com->fd[i]) < 0)                       //creo la pipe
            ft_error(com);
        i++;
    }
    i = 0;
    proc->pid = (int *)malloc(com->nchild * sizeof (int)); //alojo array de hijos
    if (com->pid < 0)
        ft_error (com);
    //freees?
}

//EXE//

void exe_command(char *order, t_pro *proc, t_env *env) 
{
    int     i;
    char    *temp_access;
	char **command;

    i = 0;
    command = ft_split(order, ' ');
    while (env->paths[i])
    {
        temp_access = ft_strjoin(env->paths[i], command[0]);
        if (!access(temp_access, X_OK))
        {
            //if(proc->nprocess > 1)
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
