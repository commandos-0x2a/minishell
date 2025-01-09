/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/08 23:17:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    wait_children(int target_pid)
{
    /* wait children */

	int	status = 0;
	int pid;
	while ((pid = waitpid(-1, &status, WUNTRACED | WCONTINUED)) != -1)
	{
		if (pid == target_pid)
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSTOPPED(status))
			{
				ft_fprintf(2, "pid: %d stopped\n", pid);
				g_status = 128 + WTERMSIG(status);
			}
			else if (WIFCONTINUED(status))
			{
				ft_fprintf(2, "pid: %d stopped\n", pid);
				g_status = 128 + WTERMSIG(status);
			}
			else if (WIFSIGNALED(status))
				g_status = 128 + WTERMSIG(status);
			else
				g_status = status;
		}
	}
}