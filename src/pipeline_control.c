/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/17 22:13:15 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_null_token(t_list *lst, int *is_pipe)
{
	*is_pipe <<= 1;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "|") == 0)
		{
			*is_pipe |= 1;
			free(lst->str);
			lst->str = NULL;
			return ;
		}
		lst = lst->next;
	}
}

static int	run_builtin_command(t_mini *mini)
{
	int		heredoc_fd;
	char	**argv;

	heredoc_fd = heredoc_forever(mini, mini->tokens);
	if (heredoc_fd < 0)
		return (PRINT_SYSCALL_ERROR, -1);
	if (redirection_handler(mini, heredoc_fd, 0) != 0)
	{
		if (heredoc_fd > 0)
			close(heredoc_fd);
		return (PRINT_SYSCALL_ERROR, -1);
	}
	if (heredoc_fd > 0)
		close(heredoc_fd);
	get_argv(&mini->tokens);
	if (argv_expander2(mini) != 0)
		return (PRINT_ALLOCATE_ERROR, -1);
	if (handle_wildcards(mini) != 0)
		return (PRINT_ALLOCATE_ERROR, -1);
	argv = lst_2_argv(&mini->tokens);
	if (!argv)
		return (PRINT_ALLOCATE_ERROR, -1);
	mini->exit_status = handle_builtin(mini, argv, 0);
	return (0);
}

/*
	if builtin run return 0 and stored exit status in mini.exit_status
	if syscall fail return -1
	return child_pid 
	<< 1 cat | << 2 cat | << 3 cat
*/
static int	pipeline_control_iter(t_mini *mini, int in_fd, int is_pipe)
{
	pid_t	victim[2];
	int		pipefds[2];

	if (!mini->tokens || !mini->tokens->str)
		return (0);
	set_null_token(mini->tokens, &is_pipe);
	if (is_pipe == 0 && is_builtin(mini, get_argv0(mini->tokens)))
		return (run_builtin_command(mini));

	if ((is_pipe & IS_NEXT_PIPE) && pipe(pipefds) == -1)
		return (-1);

	victim[0] = execute_complex_command(mini, in_fd, pipefds, is_pipe);
	if (victim[0] == -1)
	{
		if (is_pipe & IS_NEXT_PIPE)
			close(pipefds[0]);
		return (-1);
	}
	mini->exit_status = wait_child_stop(victim[0]);
	if (mini->exit_status != 128 + SIGSTOP)
		return (-2);

	if (is_pipe & IS_NEXT_PIPE)
	{
		lst_move2next(&mini->tokens);
		victim[1] = pipeline_control_iter(mini, pipefds[0], is_pipe);
		if (victim[1] < 0)
		{
			close(pipefds[0]);
			fprintf(stderr, "close: %d\n", pipefds[0]);
			kill(victim[0], SIGKILL);
			return (victim[1]);
		}
		kill(victim[0], SIGCONT);
		return (victim[1]);
	}
	kill(victim[0], SIGCONT);
	return (victim[0]);
}

int	pipeline_control(t_mini *mini)
{
	pid_t	victim;

	victim = pipeline_control_iter(mini, 0, 0);
	if (victim < 0)
	{
		wait_children(victim);
		if (victim == -1)
			return (-1);
		return (0);
	}
	if (victim > 0)
		mini->exit_status = wait_children(victim);
	return (0);
}