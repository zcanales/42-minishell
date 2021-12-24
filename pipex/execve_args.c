/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:50:54 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/24 12:56:16 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>

void ft_command(char *order, char **env)
{
    char **commands;
    char **env_paths;
    char *path;
    int i;
	int fd;

	i = 0;
    commands = ft_split(order, ' ');
	while (commands[i])
	{
		printf("command: %s\n", commands[i]);
		i++;
	}
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH", 4))
            path = env[i];
        i++;
    }
	printf("path: %s\n", path);
    path = path + 5;//quitar PATH=
	printf("path: %s\n", path);
    env_paths = ft_split(path, ':'); //posibles rutas de PATH
	i = 0;
	while (env_paths[i])
    {
        env_paths[i] = ft_strjoin(env_paths[i], "/");//añade / al final, igual mejor strlcat o algo asi
		printf("ruta %d: %s\n", i, env_paths[i]);
        if(!access(ft_strjoin(env_paths[i], commands[0]), X_OK))//Si encuentra la ruta OK:
		{
			printf("access =  %d, voy a ejecutar\n", access(ft_strjoin(env_paths[i], commands[0]), X_OK));
			fd = open("archivo.txt", O_RDONLY);
    		if (fd < 0)
        		return ;
    		dup2(fd, 0);
   			close(fd);
			execve(ft_strjoin(env_paths[i], commands[0]), commands, env);//ejecutar comando
		}
        i++;
    }
}
int main(int argc, char **argv, char **env)
{
	//int fd;
	char *order = "cat -e";

	/*fd = open("archivo.txt", O_RDONLY);
    if (fd < 0)
        return (0);
	dup2(fd, 0);
    close(fd);*/
    ft_command(order, env);
	return (0);

}
