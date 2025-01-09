/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/09 18:08:40 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int g_status;
struct termios	save_termios;




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

int main(int argc, char **argv)
{
    g_status = 0;  // Initialize exit status
	char *line;
	int is_test;
	t_config config;

	is_test = 0;

	// Load configuration
	load_config(&config);
	if (ft_strcmp(config.prompt_style, "colorful") == 0)
	{
		ft_fprintf(2, "colorful\n");
	}
	else
	{
		ft_fprintf(2, "normal\n");
	}
	if (argc == 2 && ft_strcmp(argv[1], "test") == 0)
		is_test = 1;
	while (1)
	{
		setup_signals();
		line = readline(get_prompt());
		if (!line) // ctrl-D handling
		{
			printf("\nexit\n");
			break;
		}
		handle_line(line);
		if (*line)
		{
			terminal_config(0);
			if (is_test)
				print_tokenizer(line, 0);
			else
				flow_control(line);
			terminal_reset(0);
		}
		// Restore signal handling for interactive mode
		reset_signals();
		free(line);
	}

	// Save config before exit
	save_config(&config);
	return (0);
}
