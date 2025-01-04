/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:30:52 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/04 16:33:00 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cleanup_shell(void)
{
    clear_history();
}

void    handle_line(char *line)
{
    if (line && *line)
        add_history(line);
}

char    *get_prompt(void)
{
    static char     prompt[PROMPT_MAX];
    char            hostname[HOSTNAME_MAX];
    char            cwd[PATH_MAX_LEN];
    char            *username;
    struct passwd   *pw;

    pw = getpwuid(getuid());
    username = pw ? pw->pw_name : "unknown";
    if (gethostname(hostname, sizeof(hostname)) != 0)
        strncpy(hostname, "unknown", HOSTNAME_MAX - 1);
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        strncpy(cwd, "~", PATH_MAX_LEN - 1);
    
    hostname[HOSTNAME_MAX - 1] = '\0';
    cwd[PATH_MAX_LEN - 1] = '\0';

    snprintf(prompt, PROMPT_MAX, "%.32s@%.64s:%.4096s$ ", 
             username, hostname, cwd);
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
