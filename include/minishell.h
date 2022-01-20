/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:25 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/20 16:42:33 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <unistd.h>
# include <termios.h> /*struct termios*/
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int	g_mother;

typedef struct s_piquito
{
	int		type;
	char	*file_name;
	char	**file_name_clean;
}	t_peak;

typedef struct s_ch
{
	int			id_child;
	int			nbr_command;
	char		*command_group;
	char		**command_split;
	int			nbr_infile;
	int			nbr_outfile;
	t_peak		*infile_t;
	t_peak		*outfile_t;
	int			index_in;
	int			index_out;
}	t_ch;

typedef struct s_pro
{
	int		nbr_process;
	int		*pid;
	int		**fd;
	char	**orders;
	t_ch	*child;
}	t_pro;

typedef struct s_env
{
	char	**env;
	int		nbr_env;
	char	**paths;
	char	**var_real;
	int		nbr_var;
	t_list	*list_var_real;
	t_list	*list_env;
}	t_env;

typedef struct s_shell
{
	struct termios	old;
	struct termios	changed;
	struct termios	child;
	char			*line;
	int				status;
	t_env			*my_env;
	t_pro			*my_pro;
}	t_shell;

/*	INIT	*/
void	init(t_shell **shell, char **env);
void	get_environment(t_env *my_env, char **env);

/* TERMINAL	*/
int		create_terminal(t_shell *shell);
void	attributes(t_shell *shell);
void	free_and_init(t_shell *shell);

/*PROCESSES*/
int		input(t_shell *shell);
int		alloc_processes(t_shell *shell);
void	create_processes(t_shell *shell);
void	child_process(t_ch *child, t_shell *shell);
void	mother_process(t_shell *shell);

/*CHILD_INFO*/
void	chop_files(t_ch *ch, char c, int *i, char *order);
char	*chop_command(t_ch *ch, int *i, char *order);
void	classify_order(t_ch *ch, char *order);
void	get_child_info(t_shell *shell);

/*CLEAN_COMMAND*/
void	clean_commands(t_shell *shell, t_ch *child);
void	count_nbr_commands(t_ch *child);
void	count_peaks(int *nbr_file, char c, t_peak **file_t, char *order);

/*EXECUTE*/
void	close_pipes(t_shell *shell);
void	exe_command(t_shell *shell, int id);
void	re_in_out(t_pro *pro, int in_out, int index, int id);
void	re_pipe(t_shell *shell, int id);
void	is_redirected(t_pro *pro, int id);

/*UTILS*/
void	free_double(char **s, int check);
void	ft_freelist(t_list **head);
char	*convert_array_to_string(char **array);
char	*ft_substr_strjoin(char *to_sub, char *to_join, int start, int end);
int		ft_strcmp_len(char *env, char *var);

/*	QUOTE	*/
int		check_quotes(char *s, int *index);
void	decode_quotes(t_shell *shell, char **str, int *i, int *start);
char	**fill_quote_dollar(char **array, t_shell *shell,
			int nbr_array, int check);

/*	DOLLAR	*/
char	*expand_dollar(t_shell *shell, char *str, int *i);
int		replace_dollar(char **str, int start, int len, char *replace);

/*  MOM_BUILTINS    */
void	get_real_vars(t_shell *shell, char **commnad_real,
			int nbr_commnad_real, int replace);
void	check_builtins_mother(t_shell **shell, int id);

/*PATH*/
char	**cd_builtin(char **env, char *command_split, char **new_vars);
void	get_new_paths(char **env, t_shell *shell);
char	*get_exe_path(t_shell *shell, char *command_split);

/*  EXPORT_UNSET    */
void	create_lists(t_shell *shell);
int		replace_first(t_list **head_env, t_list *temp_var, int replace);
int		replace_repeated(t_list **head_env, t_list *temp_var, int replace);
void	replace_env(t_shell *shell, int replace);
char	**convert_list_array(t_shell **shell);

/*  CHILD_BUILTINS    */
void	check_builtins_child(t_shell **shell, int id);

/* FT_SLIPT_2 */
char	**ft_split_2(char const *s, char c, int *nbr_array);

/*HERE_DOC*/
void	here_doc(t_pro *pro, int index, int id);

/*ERRORS */
int		check_error( char *line);
int		check_error_pipe(char **orders);
void	status_error(char *str, int err);

/*ERRORS */
int		check_error_pipe(char **orders);
int		pipes_check(char *line);

/*READLINE*/
void	rl_replace_line(const char *str, int i);
void	rl_clear_history(void );

#endif
