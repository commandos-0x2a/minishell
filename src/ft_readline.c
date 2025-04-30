/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:21:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/30 14:38:57 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif
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

const char *history_move_up(void);
const char *history_move_down(void);
int	ft_add_history(const char *line);
void	ft_clear_history(void);

static int	start_read(char *dst)
{
	int		i;
	ssize_t	err;
	char	c;

	i = 0;
	err = read(0, &c, 1);
	while (err > 0 && i < LINE_MAX - 1)
	{
		if (c == 4)
			return (0);
		if (c == '\n' || c == 13)
			break;
		printf("%d ", c);
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
	
	// Disable input processing
    // config.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    // Disable output processing
    // config.c_oflag &= ~(OPOST);

    // Disable canonical mode, echo, signals
    config.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    // Set character size
    // config.c_cflag |= (CS8);

    // Read returns each byte, no timeout
    config.c_cc[VMIN] = 1;
    config.c_cc[VTIME] = 0;
	
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
