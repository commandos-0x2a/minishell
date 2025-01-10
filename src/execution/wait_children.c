/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 19:31:41 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 19:31:27 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:47:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/10 19:30:55 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int wait_children(int target_pid)
{
	int	wait_status = 0;
	int	exit_code = 1;
	int child_pid;

	while ((child_pid = waitpid(target_pid, &wait_status, WUNTRACED)) != -1)
	{
		if (child_pid == target_pid)
		{
			if (WIFEXITED(wait_status))
				exit_code = WEXITSTATUS(wait_status);
			else if (WIFSTOPPED(wait_status))
			{
				ft_fprintf(2, "pid: %d stopped\n", child_pid);
				exit_code = 128 + WTERMSIG(wait_status);
				break;
			}
			else if (WIFSIGNALED(wait_status))
				exit_code = 128 + WTERMSIG(wait_status);
			else
			{
				ft_fprintf(2, "Unexpected status for pid: %d\n", child_pid);
				exit_code = wait_status;
			}
		}
	}
	return (exit_code);
}


