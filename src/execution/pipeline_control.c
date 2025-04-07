/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:32:02 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/08 01:36:16 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*clean_list(t_list **lst);

static void get_next_command(t_list *lst, int *is_pipe)
{
	*is_pipe <<= 1;
	while (lst && lst->token)
	{
		if (ft_strcmp(lst->token, "|") == 0)
		{
			*is_pipe |= 1;
			free(lst->token);
			lst->token = NULL;
			return ;
		}
		lst = lst->next;
	}
}

static int	get_nb_command(t_list *lst)
{
	int	nb_pipeline;

	nb_pipeline = 1;
	while (lst && lst->token)
	{
		if (ft_strcmp(lst->token, "|") == 0)
			nb_pipeline++;
		lst = lst->next;
	}
	return (nb_pipeline);
}

// static int	run_builtin_command(t_mdata *mdata, char **tokens)
// {
// 	int	heredoc_fd;

// 	heredoc_fd = heredoc_forever(tokens);
// 	if (heredoc_fd < 0)
// 		return (-1);
// 	if (redirection_handler(tokens, heredoc_fd, 0) != 0)
// 	{
// 		if (heredoc_fd > 0)
// 			close(heredoc_fd);
// 		return (-1);
// 	}
// 	if (heredoc_fd > 0)
// 		close(heredoc_fd);
// 	return (handle_builtin(mdata, copy_dptr(get_argv(tokens)), 0));
// }

int	pipeline_control(t_list **lst)
{
	int		is_pipe;
	int		fd;
	int		i;
	int		nb_commands;
	pid_t	victim_pid;
	pid_t	*command_pid;

	nb_commands = get_nb_command(*lst);
	// if (nb_commands == 1 && is_builtin(get_argv0(lst)))
	// 	return (run_builtin_command(mdata, pipeline));

	command_pid = ft_calloc(nb_commands, sizeof(pid_t));
	if (!command_pid)
		return (-1);
	fd = -1;
	is_pipe = 0;
	i = 0;
	while (*lst && (*lst)->token)
	{
		get_next_command(*lst, &is_pipe);
		command_pid[i] = execute_complex_command(lst, &fd, is_pipe);
		if (command_pid[i] == -1)
			break ;
		if (waitpid(command_pid[i], NULL, WUNTRACED) == -1)
			break ;
		clean_list(lst);
		i++;
	}
	if (i > 0)
		victim_pid = command_pid[i - 1];
	while (i--)
	{
		kill(command_pid[i], SIGCONT);
		waitpid(command_pid[i], NULL, WCONTINUED);
	}
	free(command_pid);
	return (wait_children(victim_pid));
}
