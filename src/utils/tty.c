/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:16:38 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/03 12:02:21 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/fs.h>  /* Definition of FICLONE* constants */
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

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
		err = dup2(fd, STDIN_FILENO);
		if (fd != STDIN_FILENO)
			close(fd);
	}
	if (err == 0 && !isatty(STDOUT_FILENO))
	{
		fd = open(tty_path, O_RDWR);
		if (fd == -1)
			return (-1);
		err = dup2(fd, STDOUT_FILENO);
		if (fd != STDOUT_FILENO)
			close(fd);
	}
	return (err);
}
