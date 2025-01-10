/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:30:52 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/10 20:02:39 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanup_shell(void)
{
	clear_history();
}

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

// int main(void)
// {
//     char    *line;

//     atexit(cleanup_shell);
//     while (1)
//     {
//         line = readline(get_prompt());
//         if (!line)
//         {
//             printf("\nexit\n");
//             break;
//         }
//         handle_line(line);
//         free(line);
//     }
//     return (0);
// }
