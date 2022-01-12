/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:08:01 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/12 20:10:50 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>

static void new_filename(t_pro *pro, int index)
{
	free(pro->child->infile_t->file_name);
	pro->child->infile_t[index].file_name = ft_strdup("here_doc.txt");
}

void here_doc(t_pro *pro, int index, int id)
{
    char    *line;
    char    *limit;
	int		fd;

    limit = ft_strdup(pro->child[id].infile_t[index].file_name);
	fd = open("here_doc.txt", O_RDWR | O_CREAT | O_APPEND, 0755);
    if (fd < 0)
    {
        free(limit);
        exit (0);
    }
	 while (1)
    {
        line = readline(">");
        if (ft_strcmp(line, limit))
        {
            free(line);
            break ;
        }
		else if (!line)
        {
            printf("exit\n");
            break;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
        line = NULL;
    }
	new_filename(pro, index);
    free(limit);
    close(fd);
	pro->fd[pro->child[id].id_child][0] = open("here_doc.txt", O_RDONLY);
}

