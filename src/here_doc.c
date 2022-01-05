/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:08:01 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/05 16:41:25 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>

void new_filename(t_pro *pro)
{
	free(pro->child->infile_t->file_name);
	pro->child->infile_t->file_name = ft_strdup("here_doc.txt");
}


void here_doc(t_pro *pro)
{
    char    *line;
    char    *limit;
    int     fd;

    limit = ft_strjoin(pro->child->infile_t->file_name, "\n");
    fd = open("here_doc.txt", O_RDWR | O_CREAT | O_APPEND, 0755);
    if (fd < 0)
    {
        free(limit);
        exit (0);
    }
	  while (1)
    {
        line = readline(">");
        if (!ft_strncmp(line, limit, ft_strlen(line)))
        {
			//kill(pro->pid[pro->child->id_child + 1], SIGCONT);
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
        line = NULL;
    }
	new_filename(pro);
   /* while (1)
    {
        line = get_next_line(0);
        if (ft_strcmp(line, limit))
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd);
        free(line);
        line = NULL;
    }*/
    free(limit);
    close(fd);
}
