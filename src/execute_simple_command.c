/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 10:29:59 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_command(t_mini *mini)
{
	char		full_path[PATH_MAX];
	int			err;
	char		**expand_argv;
	char		**argv;

	argv = lst_2_argv(&mini->tokens);
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		return ;
	}
	expand_argv = argv_expander2(mini->env, argv, 0);
	free_dptr(argv);
	if (!expand_argv)
	{
		PRINT_ALLOCATE_ERROR;
		return ;
	}
	// Check for built-in commands before getting full path and executing.
	if (is_builtin(mini->env, expand_argv[0]))
		handle_builtin(mini, expand_argv, 1);
	
	err = get_full_path(mini->env, full_path, expand_argv[0]);
	if (err == 0)
	{
		execve(full_path, expand_argv, lst_2_dptr(mini->env));
		err = 1;
	}
	free_dptr(expand_argv);
	mini_clean(mini);
	exit(err);
}
