/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/18 14:32:23 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

volatile int	g_sig;

void	mini_clean(t_mini *mini)
{
	if (mini->tokens)
		lst_clean(&mini->tokens);	
	if (mini->env)
		lst_clean(&mini->env);	
}

char *get_prompt(void)
{
    static char prompt[PROMPT_MAX];
    char cwd[PATH_MAX_LEN];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        strcpy(cwd, "~");

    cwd[PATH_MAX_LEN - 1] = '\0';
    snprintf(prompt, PROMPT_MAX, "%s$ ", cwd);
    return (prompt);
}


int main()
{
	char		*line;
	t_mini		mini;

	// if (!isatty(0) || !isatty(1) || !isatty(2))
	// {
	// 	// fds not standard
	// 	return (1);
	// }
	ft_bzero(&mini, sizeof(t_mini));
	mini.env = copy_env_variables();
	if (!mini.env)
	{
		PRINT_ALLOCATE_ERROR;
		return (1);
	}
	setup_signals();
	while (1)
	{
		line = readline(get_prompt());
		if (!line) // ctrl-D handling
		{
			printf("\nexit\n");
			break;
		}
		
		if (*line)
		{
			add_history(line);
			g_sig = 0;
			mini.tokens = tokenizer(line);
			free(line);
			if (!mini.tokens)
			{
				PRINT_ALLOCATE_ERROR;
				continue ;
			}
			if (check_syntax(mini.tokens))
			{
				// terminal_config(STDIN_FILENO);
				// reset_signals();
				flow_control(&mini);
				// terminal_reset(STDIN_FILENO);
			}
			lst_clean(&mini.tokens);
		}
	}
	mini_clean(&mini);
	return (0);
}
