/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 15:21:36 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	handle_cmd_execution(t_mini *mini, char **expand_argv)
{
	char	full_path[PATH_MAX];
	int		err;

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

void	execute_simple_command(t_mini *mini)
{
	char	**expand_argv;
	char	**argv;
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
	handle_cmd_execution(mini, expand_argv);
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
