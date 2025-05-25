/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:53:06 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/05/25 17:32:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <libft.h>

pid_t	ft_getpid(void)
{
	int		fd;
	char	*pid_str;
	char	buf[16];
	ssize_t	nbytes;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("open /proc/self/stat");
		return (-1);
	}
	nbytes = read(fd, buf, sizeof(buf));
	if (nbytes < 0)
	{
		perror("read /proc/self/stat");
		return (-1);
	}
	buf[nbytes] = '\0';
	pid_str = ft_strtok(buf, " ");
	close(fd);
	return (ft_atoi(pid_str));
}
