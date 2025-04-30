/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:21:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/30 10:23:05 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <linux/limits.h>
#include <stdio.h>
#include <termios.h>

/*
opendir, readdir, closedir,

tcsetattr, tcgetattr
tgetent, tgetflag
tgetnum, tgetstr,
tgoto, tputs
*/

#ifndef LINE_MAX
# define LINE_MAX 4096
#endif

static int	start_read(char *dst)
{
	int		i;
	ssize_t	err;
	char	c;

	i = 0;
	err = read(0, &c, 1);
	while (err > 0 && i < LINE_MAX - 1)
	{
		if (c == '\n')
			break;
		printf("%d\n", c);
		fflush(stdout);
		// if (c == 127 || c == '\b')
		// {
		// 	i--;
		// }
		// else
		// {
		dst[i] = c;
		i++;
		// }
		
		err = read(0, &c, 1);
	}
	dst[i] = '\0';
	return (err);
	
}

int	setup_terminal_config(struct termios *orginal)
{
	struct termios	config;

	tcgetattr(0, orginal);
	config = *orginal;

	tcsetattr(0, TCSANOW, &config);
	return (0);
}

char    *ft_readline(const char *prompt)
{
    char    		line[LINE_MAX];
	struct termios	orginal;

	write(1, prompt, ft_strlen(prompt));
	setup_terminal_config(&orginal);
	if (start_read(line) <= 0)
	{
		tcsetattr(0, TCSANOW, &orginal);
		return (NULL);
	}
    return (ft_strdup(line));
}
