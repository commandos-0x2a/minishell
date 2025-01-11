/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:07:47 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/11 18:27:52 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

// int *__init_in_child(void)
// {
// 	static int in_child = 0;
// 	return (&in_child);
// }

// static int g_in_child = 0;

void restore_prompt(int sig)
{
	(void)sig;
	// if (!*(__init_in_child()))
	// {
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	// }
}

void setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = restore_prompt;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

static void ignore_handler(int sig)
{
	(void)sig;
}

void reset_signals(void)
{
	signal(SIGINT, ignore_handler);
	signal(SIGQUIT, SIG_DFL);
	// signal(SIGTSTP, SIG_DFL);
}

// void set_signals_child(void)
// {
// 	*(__init_in_child()) = 1;
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }
