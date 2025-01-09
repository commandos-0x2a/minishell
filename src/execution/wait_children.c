/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 00:37:09 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    wait_children(int target_pid)
{
	int	wstatus = 0;
	int	ret = 1;
	int pid;

	while ((pid = waitpid(-1, &wstatus, WUNTRACED)) != -1)
	{
		if (pid == target_pid)
		{
			if (WIFEXITED(wstatus))
				ret = WEXITSTATUS(wstatus);
			else if (WIFSTOPPED(wstatus))
			{
				ft_fprintf(2, "pid: %d stopped\n", pid);
				ret = 128 + WTERMSIG(wstatus);
				break;
			}
			else if (WIFSIGNALED(wstatus))
				ret = 128 + WTERMSIG(wstatus);
			else
				ret = wstatus;
		}
	}
	return (ret);
}
