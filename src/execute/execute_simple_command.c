/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/25 17:31:46 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_simple_command(t_mini *mini)
{
	struct s_cmd	cmd;

	if (is_subshell(mini->tokens))
		run_subshell(mini);
	if (expand_tokens(mini, mini->tokens) != 0)
		return (1);
	cmd.argv = lst_2_argv(&mini->tokens, 1);
	if (!cmd.argv)
		return (1);
	if (is_builtin(mini, cmd.argv[0], 0))
		handle_builtin(mini, cmd.argv, 1);
	cmd.err = get_full_path(mini->env, cmd.full_path, cmd.argv[0]);
	if (cmd.err == 0)
	{
		cmd.env = lst_2_dptr(mini->env);
		cmd.err = 1;
		if (cmd.env)
		{
			cmd.err = execve(cmd.full_path, cmd.argv, cmd.env);
			print_file_error(__FILE__, __LINE__, cmd.full_path);
			free(cmd.env);
		}
	}
	free_dptr(cmd.argv);
	return (cmd.err);
}
