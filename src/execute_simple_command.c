/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 14:45:44 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_command(t_mini *mini)
{
	char		full_path[PATH_MAX];
	int			err;
	char		**argv;

	if (argv_expander2(mini) != 0)
	{
		PRINT_ALLOCATE_ERROR;
		return ;
	}
	argv = lst_2_argv(&mini->tokens);
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		return ;
	}
	// Check for built-in commands before getting full path and executing.
	if (is_builtin(mini->env, argv[0]))
		handle_builtin(mini, argv, 1);
	
	err = get_full_path(mini->env, full_path, argv[0]);
	if (err == 0)
	{
		execve(full_path, argv, lst_2_dptr(mini->env));
		err = 1;
	}
	free_dptr(argv);
	mini_clean(mini);
	exit(err);
}
