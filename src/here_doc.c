/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/04 18:25:13 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	call_here_doc(char *limiter, int out_fd)
{
	char	buffer[4096 + 1];
	ssize_t	readed;

	while (1)
	{
		write(1, "> ", 2);
		readed = read(0, buffer, 4096);
		if (readed == -1)
			return (1);
		buffer[readed] = '\0';
		if (readed > 0)
			buffer[readed - 1] = '\0';
		if (ft_strcmp(buffer, limiter) == 0)
			break ;
		if (readed > 0)
			buffer[readed - 1] = '\n';
		write(out_fd, buffer, readed);
	}
	return (0);
}

pid_t	run_here_doc_process(char *limiter, int *out_fd)
{
	pid_t	proc;
	int		pipe_fds[2];
	int		status;

	*out_fd = -1;
	if (pipe(pipe_fds) == -1)
	{
		perror("pipex: pipe");
		exit(1);
	}
	proc = fork();
	if (proc == 0)
	{
		close(pipe_fds[0]);
		status = call_here_doc(limiter, pipe_fds[1]);
		close(pipe_fds[1]);
		exit(status);
	}
	if (proc == -1)
		ft_fprintf(2, "pipex: %s: fork\n", strerror(errno));
	close(pipe_fds[1]);
	*out_fd = pipe_fds[0];
	waitpid(proc, NULL, 0);
	return (proc);
}
