/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:00 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/10 20:02:04 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_env_var(char *var)
{
    extern char **environ;
    int i, j;
    int len;

    len = 0;
    while (var[len] && var[len] != '=')
        len++;

    i = 0;
    while (environ[i])
    {
        if (strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
        {
            free(environ[i]);
            j = i;
            while (environ[j])
            {
                environ[j] = environ[j + 1];
                j++;
            }
            return;
        }
        i++;
    }
}

int ft_unset(char **argv)
{
    int i;

    if (!argv[1])
        return (0);

    i = 1;
    while (argv[i])
    {
        if (strchr(argv[i], '='))
        {
            write(2, "minishell: unset: not a valid identifier\n", 39);
            return (1);
        }
        remove_env_var(argv[i]);
        i++;
    }
    return (0);
}
