/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:07:47 by mkurkar           #+#    #+#             */
/*   Updated: 2025/03/21 12:39:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

int *heredoc_active(void)
{
	static int g_heredoc_active;
	return (&g_heredoc_active);
}

struct s_sig_handlers *get_sig_handlers(void)
{
	static struct s_sig_handlers handlers;
	return (&handlers);
}

void save_signal_handlers(void)
{
	struct s_sig_handlers *handlers = get_sig_handlers();

	sigaction(SIGINT, NULL, &handlers->old_int);
	sigaction(SIGQUIT, NULL, &handlers->old_quit);
}

void restore_signal_handlers(void)
{
	struct s_sig_handlers *handlers = get_sig_handlers();

	sigaction(SIGINT, &handlers->old_int, NULL);
	sigaction(SIGQUIT, &handlers->old_quit, NULL);
}

void restore_prompt(int sig)
{
	if (*heredoc_active())
		return;

	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
#ifdef __linux__
	rl_replace_line("", 1);
#endif
	rl_redisplay();
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
