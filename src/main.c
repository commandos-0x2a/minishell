/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:28 by mkurkar           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/13 17:39:57 by yaltayeh         ###   ########.fr       */
=======
/*   Updated: 2025/04/14 06:31:42 by yaltayeh         ###   ########.fr       */
>>>>>>> refs/remotes/origin/linked_list
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


void handle_line(char *line)
{
	if (line && *line)
		add_history(line);
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
	
	mini.env = copy_env_variables();
	if (!mini.env)
	{
		PRINT_ALLOCATE_ERROR;
		return (1);
	}


	// setup_signals();
	// terminal_config(STDIN_FILENO);
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
		
		if (*line)
		{
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
		}
	}
	lst_clean(&mini.env);
	return (0);
}
