/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:25:07 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/10 20:02:33 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_putenv(char *string)
{
    extern char **environ;
    int i, len;
    char *eq;

    if (!string || !(eq = ft_strchr(string, '=')))
        return -1;

    len = eq - string;
    i = 0;
    while (environ[i])
    {
        if (ft_strncmp(environ[i], string, len) == 0 && environ[i][len] == '=')
        {
            char *dup = ft_strdup(string);
            if (!dup)
                return -1;
            free(environ[i]);
            environ[i] = dup;
            return 0;
        }
        i++;
    }

    char **new_environ = malloc(sizeof(char *) * (i + 2));
    if (!new_environ)
        return -1;

    for (int j = 0; j < i; j++)
        new_environ[j] = environ[j];

    new_environ[i] = ft_strdup(string);
    if (!new_environ[i])
    {
        free(new_environ);
        return -1;
    }
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

    // If value is NULL, remove the variable
    if (!value)
    {
        extern char **environ;
        int i = 0, j;
        size_t name_len = ft_strlen(name);

        while (environ[i])
        {
            if (ft_strncmp(environ[i], name, name_len) == 0 &&
                environ[i][name_len] == '=')
            {
                free(environ[i]);
                for (j = i; environ[j]; j++)
                    environ[j] = environ[j + 1];
                break;
            }
            i++;
        }
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
