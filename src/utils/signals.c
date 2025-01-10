/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:07:47 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/10 20:02:40 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <signal.h>
#include <termios.h>


void restore_prompt(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
}

void setup_signals(void)
{
    // struct sigaction sa;
    
    // sa.sa_handler = restore_prompt;
    // sa.sa_flags = SA_RESTART;
    // sigemptyset(&sa.sa_mask);
    
    // sigaction(SIGINT, &sa, NULL);
    signal(SIGINT, restore_prompt);
    // signal(SIGQUIT, SIG_IGN);
    // signal(SIGTSTP, SIG_IGN);
    // signal(SIGTTIN, SIG_IGN);
    // signal(SIGTTOU, SIG_IGN);
}

static void    ignore_handler(int sig)
{
    (void)sig;
}

void reset_signals(void)
{
    signal(SIGINT, ignore_handler);
    signal(SIGQUIT, SIG_DFL);
    // signal(SIGTSTP, SIG_DFL);
}
