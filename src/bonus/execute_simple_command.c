/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/21 14:16:11 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_command(t_mini *mini)
{
	char	**argv;
	char	**env;
	char	full_path[PATH_MAX];
	int		err;

	if (is_subshell(mini->tokens))
		run_subshell(mini);
	if (expand_tokens(mini, mini->tokens) != 0)
		return ;
	argv = lst_2_argv(&mini->tokens, 1);
	if (!argv)
		return ;
	if (is_builtin(mini, argv[0], 0))
		handle_builtin(mini, argv, 1);
	err = get_full_path(mini->env, full_path, argv[0]);
	if (err == 0)
	{
		env = lst_2_dptr(mini->env);
		if (!env)
		{
			free_dptr(argv);
			return ;
		}
		execve(full_path, argv, env);
		free_dptr(env);
		PRINT_FILE_ERROR(full_path);
		err = 1;
	}
	free_dptr(argv);
	mini_clean(mini);
	exit(err);
}
