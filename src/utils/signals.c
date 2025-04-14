/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:07:47 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/14 15:10:39 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

typedef enum e_signal_event
{
	SIG_HEREDOC_ACTIVE,
	SIG_INTERACTIVE_MODE,
	SIG_EXECUTION_MODE,
	SIG_INT_HANDLER,
	SIG_QUIT_HANDLER
}	t_signal_event;

typedef enum e_setter
{
	SIG_SET,
	SIG_RETURN,
}	t_setter;

static int	handle_mode_events(t_signal_event event, int set_value, int is_setter)
{
	static int	heredoc_active = 0;
	static int	interactive_mode = 0;
	static int	execution_mode = 0;

	if (event == SIG_HEREDOC_ACTIVE)
	{
		if (is_setter)
			heredoc_active = set_value;
		return (heredoc_active);
	}
	else if (event == SIG_INTERACTIVE_MODE)
	{
		if (is_setter)
			interactive_mode = set_value;
		return (interactive_mode);
	}
	else if (event == SIG_EXECUTION_MODE)
	{
		if (is_setter)
			execution_mode = set_value;
		return (execution_mode);
	}
	return (0);
}

static int	handle_handler_events(t_signal_event event, int is_setter)
{
	static struct sigaction	old_int;
	static struct sigaction	old_quit;

	if (event == SIG_INT_HANDLER)
	{
		if (is_setter)
			return (sigaction(SIGINT, NULL, &old_int));
		return (sigaction(SIGINT, &old_int, NULL));
	}
	else if (event == SIG_QUIT_HANDLER)
	{
		if (is_setter)
			return (sigaction(SIGQUIT, NULL, &old_quit));
		return (sigaction(SIGQUIT, &old_quit, NULL));
	}
	return (0);
}

static int	signal_controller(t_signal_event event, int set_value, int is_setter)
{
	if (event <= SIG_EXECUTION_MODE)
		return (handle_mode_events(event, set_value, is_setter));
	else
		return (handle_handler_events(event, is_setter));
}

static void	restore_prompt(int sig)
{
	if (signal_controller(SIG_HEREDOC_ACTIVE, 0, SIG_SET))
		return ;
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
#ifdef __linux__
	rl_replace_line("", 1);
#endif
	rl_redisplay();
}

static void	ignore_handler(int sig)
{
	(void)sig;
}

int	heredoc_is_active(void)
{
	return (signal_controller(SIG_HEREDOC_ACTIVE, 0, SIG_SET));
}

void	set_heredoc_active(int active)
{
	signal_controller(SIG_HEREDOC_ACTIVE, active, 1);
}

void	save_signal_handlers(void)
{
	signal_controller(SIG_INT_HANDLER, 0, 1);
	signal_controller(SIG_QUIT_HANDLER, 0, 1);
}

void	restore_signal_handlers(void)
{
	signal_controller(SIG_INT_HANDLER, 0, SIG_SET);
	signal_controller(SIG_QUIT_HANDLER, 0, SIG_SET);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = restore_prompt;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal_controller(SIG_INTERACTIVE_MODE, 1, SIG_RETURN);
	signal_controller(SIG_EXECUTION_MODE, 0, SIG_RETURN);
}

void	reset_signals(void)
{
	signal(SIGINT, ignore_handler);
	signal(SIGQUIT, SIG_DFL);
	signal_controller(SIG_INTERACTIVE_MODE, 0, SIG_RETURN);
	signal_controller(SIG_EXECUTION_MODE, 1, SIG_RETURN);
}
