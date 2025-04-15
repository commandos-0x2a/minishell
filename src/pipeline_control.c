/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 23:38:22 by yaltayeh         ###   ########.fr       */
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

static int	get_nb_command(t_list *lst)
{
	int	nb_pipeline;

	nb_pipeline = 1;
	while (lst && lst->str)
	{
		if (ft_strcmp(lst->str, "|") == 0)
			nb_pipeline++;
		lst = lst->next;
	}
	return (nb_pipeline);
}

static int	run_builtin_command(t_mini *mini)
{
	int	heredoc_fd;
	char	**argv;

	heredoc_fd = heredoc_forever(mini, mini->tokens);
	if(mini->is_interupted)
	{
		if (heredoc_fd > 0)
			close(heredoc_fd);
		mini->is_interupted = 0;
		return (mini->exit_status);
	}
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
	return (handle_builtin(mini, argv, 0));
}

int	pipeline_control(t_mini *mini)
{
	int		is_pipe;
	int		fd;
	int		i;
	int		nb_commands;
	pid_t	victim_pid;
	pid_t	*command_pid;
	int		wstatus;

	nb_commands = get_nb_command(mini->tokens);
	if (nb_commands == 1 && is_builtin(mini, get_argv0(mini->tokens)))
		return (run_builtin_command(mini));

	command_pid = ft_calloc(nb_commands, sizeof(pid_t));
	if (!command_pid)
		return (-1);
	mini->ctx = command_pid;
	fd = -1;
	is_pipe = 0;
	i = 0;
	while (mini->tokens && mini->tokens->str)
	{
		set_null_token(mini->tokens, &is_pipe);
		command_pid[i] = execute_complex_command(mini, &fd, is_pipe);
		if (command_pid[i] == -1)
			break ;
		mini->exit_status = wait_child_stop(command_pid[i]);
		if (mini->exit_status != 128 + SIGSTOP)
		{
			while (i--)
				kill(command_pid[i], SIGKILL);
			free(command_pid);
			if (fd > 0)
				close(fd);
			mini->ctx = NULL;
			return (mini->exit_status);
		}
		i++;
		if ((is_pipe & IS_PIPE) == 0)
			break ;
		lst_move2next(&mini->tokens);
	}
	if (i > 0)
		victim_pid = command_pid[i - 1];
	i = 0;
	while (i < nb_commands)
	{
		if (command_pid[i] != -1)
			kill(command_pid[i], SIGCONT);
		i++;
	}
	free(command_pid);
	mini->ctx = NULL;
	return (wait_children(victim_pid));
}
