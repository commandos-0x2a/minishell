/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/14 20:20:09 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_children(int target_pid)
{
	int	wstatus;
	int	exit_code;
	int	child_pid;

	exit_code = 1;
	child_pid = waitpid(-1, &wstatus, WUNTRACED);
	while (child_pid != -1)
	{
		// if (child_pid == target_pid)
		// {
			if (WIFEXITED(wstatus))
			{
				// ft_fprintf(2, "%d: is exited by %d\n", \
				// 		child_pid, WEXITSTATUS(wstatus));
				exit_code = WEXITSTATUS(wstatus);
			}
			else if (WIFSIGNALED(wstatus))
			{
				// ft_fprintf(2, "%d: is signaled by %d\n", \
				// 		child_pid, WTERMSIG(wstatus));
				exit_code = 128 + WTERMSIG(wstatus);
			}
			// else if (WIFCONTINUED(wstatus))
			// 	ft_fprintf(2, "%d: is continued\n", child_pid);
			// else if (WIFSTOPPED(wstatus))
			// 	ft_fprintf(2, "%d: is stopped\n", child_pid);
		// }
		child_pid = waitpid(-1, &wstatus, WUNTRACED);
	}
	if (target_pid == -1)
		return (1);
	return (exit_code);
}
