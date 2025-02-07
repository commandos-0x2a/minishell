/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/02/07 17:22:30 by yaltayeh         ###   ########.fr       */
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
		if (child_pid == target_pid)
		{
			if (WIFEXITED(wstatus))
				exit_code = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_code = 128 + WTERMSIG(wstatus);
			else if (WIFCONTINUED(wstatus))
				ft_fprintf(2, "%d: is stopped\n", child_pid);
			else if (WIFSTOPPED(wstatus))
				ft_fprintf(2, "%d: is stopped\n", child_pid);
		}
		child_pid = waitpid(-1, &wstatus, WUNTRACED);
	}
	return (exit_code);
}
