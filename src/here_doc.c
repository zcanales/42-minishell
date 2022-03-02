/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:08:01 by eperaita          #+#    #+#             */
/*   Updated: 2022/03/01 21:10:53 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>

//HERE_DOC -> Opens the STDIN and saves all in here_doc.txt
	//HERE_DOC_LOOP -> Reading from STDIN
	//NEW_FILENAME -> Sends filename as arg to child

static void	new_filename(t_pro *pro, int index, int id)
{
	free(pro->child[id].infile_t[index].file_name);
	pro->child[id].infile_t[index].file_name = ft_strdup("here_doc.txt");
}

static void	here_doc_loop(char *limit, int fd)
{
	char	*line;

	//printf("%s\n", limit);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, limit))
		{
			free(line);
			break ;
		}
		else if (!line)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = NULL;
	}
}

void	here_doc(t_pro *pro, int index, int id)
{
	char	*limit;
	int		fd;

	g_mother = 3;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	limit = ft_strdup(pro->child[id].infile_t[index].file_name);
	fd = open("here_doc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		status_error(strerror(errno), errno);
	here_doc_loop(limit, fd);
	new_filename(pro, index, id);
	free(limit);
	close(fd);
	pro->fd[pro->child[id].id_child][0] = open("here_doc.txt", O_RDONLY);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
