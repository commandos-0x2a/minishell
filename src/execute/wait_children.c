/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/25 17:32:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG

static int	get_process_status(int wstatus, pid_t victim)
{
	if (WIFEXITED(wstatus))
	{
		ft_fprintf(2, "%d: is exited by %d\n", victim, WEXITSTATUS(wstatus));
		return (WEXITSTATUS(wstatus));
	}
	else if (WIFSIGNALED(wstatus))
	{
		ft_fprintf(2, "%d: is signaled by %d\n", victim, WTERMSIG(wstatus));
		return (128 + WTERMSIG(wstatus));
	}
	else if (WIFSTOPPED(wstatus))
	{
		ft_fprintf(2, "%d: is stopped\n", victim);
		return (128 + SIGSTOP);
	}
	else if (WIFCONTINUED(wstatus))
	{
		ft_fprintf(2, "%d: is continued\n", victim);
		return (128 + SIGCONT);
	}
	return (1);
}

#else

static int	get_process_status(int wstatus, pid_t victim)
{
	(void)victim;
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	else if (WIFSTOPPED(wstatus))
		return (128 + SIGSTOP);
	else if (WIFCONTINUED(wstatus))
		return (128 + SIGCONT);
	return (1);
}

#endif

int	wait_one_child(pid_t victim)
{
	int	wstatus;
	int	status;

	if (waitpid(victim, &wstatus, WUNTRACED) == -1)
		return (-1);
	status = get_process_status(wstatus, victim);
	return (status);
}

int	wait_all_childrens(pid_t victim)
{
	int	wstatus;
	int	status;
	int	ret_status;
	int	child_pid;

	ret_status = 1;
	child_pid = waitpid(WAIT_ANY, &wstatus, WUNTRACED);
	while (child_pid != -1)
	{
		status = get_process_status(wstatus, child_pid);
		if (child_pid == victim)
			ret_status = status;
		child_pid = waitpid(WAIT_ANY, &wstatus, WUNTRACED);
	}
	return (ret_status);
}
