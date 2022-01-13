/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:35:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/01/13 20:06:15 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//SORT_BUILTINGS- export - unset - cd - pwd - echo
//REALLOC_ENV
//ALLOC_NEW_VARS

#include "../include/minishell.h"
//Crear solo la lista env
void create_lists(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->my_env->env[++i])
	{
		ft_lstadd_back(&shell->my_env->list_env, ft_lstnew(shell->my_env->env[i]));
	}
	i = -1;
   	while (shell->my_env->var_real[++i])
	{
		if (shell->my_env->var_real[i][0] != '=' && (ft_isalpha(shell->my_env->var_real[i][0]) || shell->my_env->var_real[i][0] == '_'))
		{
			printf("Variable alojada: %s \n", &shell->my_env->var_real[i][0]);
        	ft_lstadd_back(&shell->my_env->list_var_real, ft_lstnew(shell->my_env->var_real[i]));
		}
		else
			printf("No valido FIN var %s \n", &shell->my_env->var_real[i][0]);
	}
}

int replace_repeated(t_list *temp_env, t_list *temp_var)
{
	int len;

	while (temp_env)
	{
		len = ft_strlen((char *)temp_var->content)
		   	- ft_strlen(ft_strchr((char *)temp_var->content, '='));
		if (!ft_strncmp((char *)temp_var->content, (char *)temp_env->content, len))
		{
			free(temp_env->content);
			temp_env->content = ft_strdup(temp_var->content);
			return (0);
		}
		temp_env = temp_env->next;
	}
	return (1);
}	

void replace_env(t_shell *shell) 
{
	t_list *temp_var;

	temp_var = shell->my_env->list_var_real;
	while (temp_var)
	{
			if (replace_repeated(shell->my_env->list_env, temp_var))
				ft_lstadd_back(&shell->my_env->list_env, ft_lstnew((char *)temp_var->content));
			temp_var = temp_var->next;
	}
	ft_freelist(&shell->my_env->list_var_real);
}


char **convert_list_array(t_shell *shell)
{
	char **temp_env;
	int i;

	i = -1;
	
	shell->my_env->nbr_env = ft_lstsize(shell->my_env->list_env);
	temp_env= (char **)malloc(sizeof(char *) * (shell->my_env->nbr_env + 1));
	if (!temp_env)
		exit(1);
	while (shell->my_env->list_env)
	{
		temp_env[++i] = ft_strdup((char *)shell->my_env->list_env->content);
		shell->my_env->list_env = shell->my_env->list_env->next;
	}
	temp_env[shell->my_env->nbr_env] = NULL;
	free_double(shell->my_env->env);
	shell->my_env->env = NULL;
	return (temp_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void	check_builtins_child(t_shell **shell, int id)
{
	if (!ft_strncmp((*shell)->my_pro->child[id].command_split[0], "export", ft_strlen("export")))
	{
	printf("Soy el hijo tengo export --> MUERO\n");
		exit(0);
	}
	else if (ft_strcmp((*shell)->my_pro->child[id].command_split[0], "unset"))
		exit(0);
}
   
void    check_builtins_mother(t_shell **shell, int id)
{
	int i;

    if (!ft_strncmp((*shell)->my_pro->child[id].command_split[0], "export", ft_strlen("export")) && !(*shell)->my_pro->child[id].command_split[0][6])
	{
		printf("Soy la madre y tengo export --> %s \n",(*shell)->my_pro->child[id].command_split[0]);
		get_real_vars(*shell, (*shell)->my_pro->child[id].command_split, (*shell)->my_pro->child[id].nbr_command);
		create_lists(*shell);
		replace_env((*shell));
		(*shell)->my_env->env = convert_list_array(*shell);

	}
    if (!ft_strncmp((*shell)->my_pro->child[id].command_split[0], "env", ft_strlen("env")) && !(*shell)->my_pro->child[id].command_split[0][3])
	{
		i = -1;
		//ya lo hace solo, como si fuera un binario. Si lo hcemos builtin, impedimos su ejecucion en hijo?
		/*while ((*shell)->my_env->env[++i])
			printf("%s\n", (*shell)->my_env->env[i]);*/
	}
}
