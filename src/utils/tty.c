/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:16:38 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/28 05:54:14 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include <linux/limits.h>

int	ft_ttyname_r(int fd, char *buf, size_t len)
{
	char	*tty_path;

	tty_path = ttyname(fd);
	if (!tty_path)
		return (-1);
	if (ft_strlcpy(buf, tty_path, len) >= len)
		return (-1);
	return (0);
}

int	restore_tty(char tty_path[PATH_MAX])
{
	int	fd;
	int	err;

	err = 0;
	if (!isatty(STDIN_FILENO))
	{
		fd = open(tty_path, O_RDWR);
		if (fd == -1)
			return (-1);
		if (fd != STDIN_FILENO)
		{
			err = dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	if (err == 0 && !isatty(STDOUT_FILENO))
	{
		fd = open(tty_path, O_RDWR);
		if (fd == -1)
		return (-1);
		if (fd != STDOUT_FILENO)
		{
			err = dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	return (err);
}
