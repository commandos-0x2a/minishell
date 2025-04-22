/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/22 15:15:22 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_null_token(t_list *lst, int *pipe_mask)
{
	*pipe_mask <<= 1;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "|") == 0)
		{
			*pipe_mask |= 1;
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
	if (expand_tokens(mini, mini->tokens) != 0)
		return (PRINT_ALLOCATE_ERROR, -1);
	argv = lst_2_argv(&mini->tokens, 0);
	if (!argv)
		return (PRINT_ALLOCATE_ERROR, -1);
	mini->exit_status = handle_builtin(mini, argv, 0);
	return (0);
}

static pid_t	execute_command(t_mini *mini, int in_fd,	\
								int pipefds[2], int pipe_mask)
{
	pid_t	victim;

	victim = execute_complex_command(mini, in_fd, pipefds, pipe_mask);
	if (victim == -1)
	{
		if (pipe_mask & IS_NEXT_PIPE)
			close(pipefds[0]);
		return (-1);
	}
	mini->exit_status = wait_child_stop(victim);
	if (mini->exit_status != 128 + SIGSTOP)
	{
		if (pipe_mask & IS_NEXT_PIPE)
			close(pipefds[0]);
		return (-2);
	}
	return (victim);
}

/*
	if builtin run return 0 and stored exit status in mini.exit_status
	if syscall fail return -1
	return child_pid 
	valgrind --leak-check=full --show-leak-kinds=all
			--trace-children=yes --track-fds=yes
			--suppressions=readline_curses.supp ./minishell
	<< 1 cat > 1 | << 2 cat > 2| << 3 cat > 3
*/
static int	pipeline_control_iter(t_mini *mini, int in_fd, int pipe_mask)
{
	pid_t	victim[2];
	int		pipefds[2];

	set_null_token(mini->tokens, &pipe_mask);
	if (pipe_mask == 0 && is_builtin(mini, get_argv0(mini->tokens), 1))
		return (run_builtin_command(mini));
	if ((pipe_mask & IS_NEXT_PIPE) && pipe(pipefds) == -1)
		return (-1);
	victim[0] = execute_command(mini, in_fd, pipefds, pipe_mask);
	if (victim[0] < 0)
		return (victim[0]);
	if ((pipe_mask & IS_NEXT_PIPE) && mini->tokens && mini->tokens->str)
	{
		lst_move2next(&mini->tokens);
		victim[1] = pipeline_control_iter(mini, pipefds[0], pipe_mask);
		if (victim[1] == -1)
			kill(victim[0], SIGKILL);
		else
			kill(victim[0], SIGCONT);
		close(pipefds[0]);
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
