/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/13 02:05:00 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_2_argv(t_tokens **lst, int i)
{
	char	**argv;
	t_tokens	*current;

	if (!*lst || !(*lst)->token)
	{
		tok_clean(lst);
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

void	execute_simple_command(t_mini *mini)
{
	char		full_path[PATH_MAX];
	int			err;
	char		**expand_argv;
	char		**argv;

	argv = lst_2_argv(&mini->tokens, 0);
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		exit(1);
	}
	
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
