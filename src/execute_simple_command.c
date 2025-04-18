/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/18 14:32:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	exit_handler(t_mini *mini, int exit_status);

static void	run_subshell(t_mini *mini)
{
	char	*argv0;
	size_t	line_len;
	char	*line;

	argv0 = get_argv0(mini->tokens);
	++argv0;
	line_len = ft_strlen(argv0);
	if (argv0[line_len - 1] != ')')
		exit_handler(mini, 1);
	argv0[line_len - 1] = '\0';
	line = ft_strdup(argv0);
	if (!line)
		exit_handler(mini, 1);
	lst_clean(&mini->tokens);
	mini->tokens = tokenizer(line);
	free(line);
	if (!mini->tokens)
		exit_handler(mini, 1);
	if (flow_control(mini) != 0)
	{
		perror("flow_control");
		exit_handler(mini, 1);
	}
	exit_handler(mini, 0);	
}

static int	is_subshell(t_mini *mini)
{
	char	*argv0;

	argv0 = get_argv0(mini->tokens);
	if (!argv0)
		return (0);
	if (*argv0 == '(')
		return (1);
	return (0);
}

void	execute_simple_command(t_mini *mini)
{
	char	**argv;
	char	full_path[PATH_MAX];
	int		err;

	if (is_subshell(mini))
		run_subshell(mini);
	if (argv_expander2(mini) != 0)
		return ;
	if (handle_wildcards(mini) != 0)
		return ;
	argv = lst_2_argv(&mini->tokens);
	if (!argv)
		return ;
	if (is_builtin(mini, argv[0]))
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
