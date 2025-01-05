/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:25:07 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/05 17:30:36 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int ft_putenv(char *string)
{
    extern char **environ;
    int i;
    char *eq;
    size_t namelen;

    if (!string || !(eq = ft_strchr(string, '=')))
        return -1;

    namelen = eq - string;
    i = 0;
    while (environ[i])
    {
        if (ft_strncmp(environ[i], string, namelen) == 0 && environ[i][namelen] == '=')
        {
            environ[i] = string;
            return 0;
        }
        i++;
    }

    // Allocate new environment array
    char **new_environ = ft_calloc(i + 2, sizeof(char *));
    if (!new_environ)
        return -1;

    // Copy old environment
    for (int j = 0; j < i; j++)
        new_environ[j] = environ[j];

    new_environ[i] = string;
    new_environ[i + 1] = NULL;
    environ = new_environ;

    return 0;
}

int ft_setenv(const char *name, const char *value, int overwrite)
{
    char *current;
    char *new_var;

    if (!name || ft_strchr(name, '=') != NULL)
        return -1;

    current = ft_getenv(name);
    if (current != NULL && !overwrite)
    {
        free(current);
        return 0;
    }

    // Allocate space for "name=value\0"
    new_var = malloc(ft_strlen(name) + (value ? ft_strlen(value) : 0) + 2);
    if (!new_var)
        return -1;

    strcpy(new_var, name);
    strcat(new_var, "=");
    if (value)
        strcat(new_var, value);

    int ret = ft_putenv(new_var);
    if (ret != 0)
        free(new_var);

    if (current)
        free(current);

    return ret;
}
