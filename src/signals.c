/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:07:47 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/08 17:56:57 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <signal.h>
#include <termios.h>



static void restore_prompt(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void setup_signals(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOK;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    signal(SIGINT, restore_prompt);
    signal(SIGQUIT, SIG_IGN);
    // Set up signal handlers
    signal(SIGINT, restore_prompt);   // ctrl-C
    signal(SIGQUIT, SIG_IGN);        // ctrl- \/
}

void reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
