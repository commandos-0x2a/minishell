/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/13 17:39:57 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

struct termios	save_termios;

char	*add_space_to_line(const char *s);

char *ft_itoa_kur(int n);

void init_shell_level(void)
{
	char *shlvl_str;
	int shlvl;
	char *level;

	shlvl_str = getenv("SHLVL");
	if (!shlvl_str || !*shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = 0;
		else if (shlvl >= 999)
			shlvl = 1;
		else
			shlvl++;
	}

	level = ft_itoa_kur(shlvl);
	setenv("SHLVL", level, 1);
}

int	terminal_config(int fd)
{
	struct termios	term;

	if (tcgetattr(fd, &term) < 0)
		return (-1);
	save_termios = term; /* structure copy */

	term.c_lflag &= ~(ECHOCTL);

	if (tcsetattr(fd, TCSAFLUSH, &term) < 0)
		return (-1);
	return (0);
}

int	terminal_reset(int fd)
{
	if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
		return(-1);
	return(0);
}

int main()
{
	char		*line;
	char		*expand_line;
	t_mini		mini;

	// t_config	config;

	// setup_signals();
	// terminal_config(STDIN_FILENO);

	// if (!isatty(0) || !isatty(1) || !isatty(2))
	// {
	// 	// fds not standard
	// 	return (1);
	// }
	
	while (1)
	{
		// setup_signals();
		line = readline(get_prompt());
		
		// reset_signals();

		if (!line) // ctrl-D handling
		{
			printf("\nexit\n");
			break;
		}
		handle_line(line);
		expand_line = add_space_to_line(line);
		free(line);
		if (!expand_line)
		{
			PRINT_ALLOCATE_ERROR;
			break;
		}
		
		if (*expand_line)
		{
			mini.tokens = tokenizer(expand_line);
			free(expand_line);
			if (!mini.tokens)
			{
				// PRINT_ALLOCATE_ERROR;
				continue ;
			}
			if (check_syntax(mini.tokens))
			{
				// terminal_config(STDIN_FILENO);
				// reset_signals();
				flow_control(&mini);
				// terminal_reset(STDIN_FILENO);
			}
		}
	}
	cleanup_env_copy();
	return (0);
}
