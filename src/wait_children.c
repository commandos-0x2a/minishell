/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/15 23:57:58 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_process_status(int wstatus, pid_t pid)
{
	if (WIFEXITED(wstatus))
	{
		ft_fprintf(2, "%d: is exited by %d\n", pid, WEXITSTATUS(wstatus));
		return (WEXITSTATUS(wstatus));
	}
	else if (WIFSIGNALED(wstatus))
	{
		ft_fprintf(2, "%d: is signaled by %d\n", pid, WTERMSIG(wstatus));
		return (128 + WTERMSIG(wstatus));
	}
	else if (WIFSTOPPED(wstatus))
	{
		ft_fprintf(2, "%d: is stopped\n", pid);
	 	return (128 + SIGSTOP);
	}
	else if (WIFCONTINUED(wstatus))
	{
		ft_fprintf(2, "%d: is continued\n", pid);
		return (128 + SIGCONT);
	}
	return (-1);
}

int	wait_child_stop(pid_t victim)
{
	int	wstatus;

	if (waitpid(victim, &wstatus, WUNTRACED) == -1)
		return (-1);
	return (get_process_status(wstatus, victim));
}

int	wait_children(int target_pid)
{
	int	wstatus;
	int	process_status;
	int	child_pid;

	process_status = 1;
	child_pid = waitpid(WAIT_ANY, &wstatus, WUNTRACED);
	while (child_pid != -1)
	{
		// if (child_pid == target_pid)
		// {
			process_status = get_process_status(wstatus, child_pid);
		// }
		child_pid = waitpid(-1, &wstatus, WUNTRACED);
	}
	if (target_pid == -1)
		return (1);
	return (process_status);
}
