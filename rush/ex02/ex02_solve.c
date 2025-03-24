/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex01_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:39:52 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/23 20:13:12 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int	in_fd;
	int	out_fd;

	if (fork() == 0)
	{
		in_fd = open("in", O_RDONLY);
		if (in_fd == -1)
		{
			perror("in");
			exit(1);
		}
		if (dup2(in_fd, 10) == -1)
		{
			perror("dup2 in_fd");
			exit(1);
		}
		close(in_fd);
		out_fd = open("out", O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (out_fd == -1)
		{
			perror("out");
			exit(1);
		}
		if (dup2(out_fd, 15) == -1)
		{
			perror("dup2 out_fd");
			exit(1);
		}
		close(out_fd);
		char *argv[] = {
			"./ex00_test",
			"10",
			"15",
			NULL
		};
		execve("./ex00_test", argv, NULL);
		perror("execve");
		exit(1);
	}
	wait(NULL);
	return (0);
}