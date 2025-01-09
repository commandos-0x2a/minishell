/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/09 18:28:48 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    wait_children(int target_pid)
{
    /* wait children */

	int	wstatus = 0;
	int	ret = 1;
	int pid;
	while ((pid = waitpid(-1, &wstatus, WUNTRACED | WCONTINUED)) != -1)
	{
		if (pid == target_pid)
		{
			if (WIFEXITED(wstatus))
				ret = WEXITSTATUS(wstatus);
			else if (WIFSTOPPED(wstatus))
			{
				ft_fprintf(2, "pid: %d stopped\n", pid);
				ret = 128 + WTERMSIG(wstatus);
			}
			else if (WIFCONTINUED(wstatus))
			{
				ft_fprintf(2, "pid: %d stopped\n", pid);
				ret = 128 + WTERMSIG(wstatus);
			}
			else if (WIFSIGNALED(wstatus))
				ret = 128 + WTERMSIG(wstatus);
			else
				ret = wstatus;
		}
	}
	return (ret);
}
