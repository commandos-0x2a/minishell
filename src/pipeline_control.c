/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 09:26:34 by yaltayeh         ###   ########.fr       */
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
	char	**expand_argv;

	heredoc_fd = heredoc_forever(mini->tokens, mini->env);
	if (heredoc_fd < 0)
		return (-1);
	if (redirection_handler(mini->tokens, mini->env, heredoc_fd, 0) != 0)
	{
		if (heredoc_fd > 0)
			close(heredoc_fd);
		return (-1);
	}
	if (heredoc_fd > 0)
		close(heredoc_fd);
	get_argv(&mini->tokens);
	argv = lst_2_dptr(mini->tokens);
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;	
		return (-1);
	}
	expand_argv = argv_expander2(mini->env, argv, 0);
	free_dptr(argv);
	if (!expand_argv)
	{
		PRINT_ALLOCATE_ERROR;	
		return (-1);
	}
	return (handle_builtin(mini, expand_argv, 0));
}

int	pipeline_control(t_mini *mini)
{
	int		is_pipe;
	int		fd;
	int		i;
	int		nb_commands;
	pid_t	victim_pid;
	pid_t	*command_pid;

	nb_commands = get_nb_command(mini->tokens);
	if (nb_commands == 1 && is_builtin(mini->env, get_argv0(mini->tokens)))
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
		if (waitpid(command_pid[i], NULL, WUNTRACED) == -1)
			break ;
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
	return (wait_children(victim_pid));
}
