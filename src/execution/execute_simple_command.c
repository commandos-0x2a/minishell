/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/08 01:52:52 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*fclean_list(t_list *lst);

static void	run_subshell(char **argv)
{
	char	*line;
	int		status;
	t_list	*lst;

	if (argv[1] != NULL)
		exit(222);
	line = *argv;
	line[ft_strlen(line) - 1] = '\0';
	line++;
	line = ft_strdup(line);
	if (!line)
	{
		PRINT_ALLOCATE_ERROR;
		exit(1);
	}
	lst = tokenizer(line);
	free(line);
	status = pipeline_control(&lst);

	exit(status);
}

char	**lst_2_argv(t_list **lst, int i)
{
	char	**argv;
	t_list	*current;

	if (!*lst || !(*lst)->token)
	{
		fclean_list(*lst);
		return (ft_calloc(i + 1, sizeof(char *)));
	}
	current = *lst;
	*lst = (*lst)->next;
	argv = lst_2_argv(lst, i + 1);
	if (!argv)
		free(current->token);
	else
		argv[i] = current->token;
	free(current);
	return (argv);
}

void	execute_simple_command(t_list **lst)
{
	char		full_path[PATH_MAX];
	int			err;
	char		**expand_argv;
	char		**argv;

	argv = lst_2_argv(lst, 0);
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		exit(1);
	}
	
	// Check if the first character of the command is an opening parenthesis
	if ((*argv)[0] == '(')
		run_subshell(argv);
	
	expand_argv = argv_expander2(argv, 0);
	free_dptr(argv);
	if (!expand_argv)
	{
		PRINT_ALLOCATE_ERROR;
		exit(1);
	}	
	// Check for built-in commands before getting full path and executing.
	if (is_builtin(expand_argv[0]))
		handle_builtin(expand_argv, 1);
	
	err = get_full_path(full_path, expand_argv[0]);
	if (err == 0)
	{
		execve(full_path, expand_argv, *__init__env());
		perror(PREFIX"execve");
		err = 1;
	}
	free_dptr(expand_argv);
	cleanup_env_copy();
	exit(err);
}
