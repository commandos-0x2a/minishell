/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:42:59 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/01 16:51:19 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	call_here_doc(char *limiter, int out_fd)
{
	char	buffer[4096];
	ssize_t	_read;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		write(1, "> ", 2);
		_read = read(0, buffer, sizeof(buffer));
		if (_read == -1)
			return (1);
		if (_read == 0)
		{
			ft_dprintf(2, "\npipex: warning: here-document " \
						"delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (ft_strncmp(buffer, limiter, limiter_len - 1) == 0 \
						&& buffer[limiter_len] == '\n')
			break ;
		write(out_fd, buffer, _read);
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
		exit_handler("pipe", 1);
	proc = fork();
	if (proc == 0)
	{
		close(pipe_fds[0]);
		status = call_here_doc(limiter, pipe_fds[1]);
		close(pipe_fds[1]);
		exit(status);
	}
	if (proc == -1)
		ft_dprintf(2, "pipex: %s: fork\n", strerror(errno));
	close(pipe_fds[1]);
	*out_fd = pipe_fds[0];
	waitpid(proc, &status, 0);
	return (proc);
}
