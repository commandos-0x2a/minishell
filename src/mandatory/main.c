/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/20 02:09:04 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

void	mini_clean(t_mini *mini)
{
	if (mini->tokens)
		lst_clean(&mini->tokens);	
	if (mini->env)
		lst_clean(&mini->env);	
}

void	exit_handler(t_mini *mini, int exit_status)
{
	mini_clean(mini);
	if (g_sig != 0)
		exit(128 + g_sig);
	exit(exit_status);
}

char *get_prompt(void)
{
    static char prompt[PROMPT_MAX];
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        strcpy(cwd, "~");

    cwd[PATH_MAX - 1] = '\0';
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
	setup_signals2();
	ft_bzero(&mini, sizeof(t_mini));
	mini.env = copy_env_variables();
	if (!mini.env)
	{
		PRINT_ALLOCATE_ERROR;
		return (1);
	}
	while (1)
	{
		setup_signals();
		line = readline(get_prompt());
		setup_signals2();
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
				pipeline_control(&mini);
			lst_clean(&mini.tokens);
		}
	}
	mini_clean(&mini);
	return (0);
}
