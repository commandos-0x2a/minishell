/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/08 20:55:54 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int g_status;

char *ft_itoa_kur(int n);

static void init_shell_level(void)
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

int main(int argc, char **argv)
{
	char *line;
	int is_test;
	t_config config;


	// Terminal configuration and signal handling (terminal control => tc)
	// Move shell to foreground and take control of terminal
	while (tcgetpgrp(STDIN_FILENO) != getpgrp())
		kill(getpid(), SIGTTIN);
	
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	
	setpgid(0, 0);
	tcsetpgrp(STDIN_FILENO, getpgrp());

	init_shell_level();
	is_test = 0;
	setup_signals();

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
		line = readline(get_prompt());
		if (!line) // ctrl-D handling
		{
			printf("\nexit\n");
			break;
		}
		reset_signals();
		handle_line(line);
		if (*line)
		{
			if (is_test)
				print_tokenizer(line, 0);
			else
				flow_control(line);
		}
		// Restore signal handling for interactive mode
		free(line);
		setup_signals();
	}

	// Save config before exit
	save_config(&config);
	return (0);
}
