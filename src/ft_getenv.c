/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 07:25:20 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/09 15:58:18 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(const char *name)
{
    extern char **environ;
    size_t name_len;
    int i;

    if (!name)
        return (NULL);
    
    name_len = ft_strlen(name);
    i = 0;
    while (environ[i])
    {
        if (ft_strncmp(environ[i], name, name_len) == 0 && 
            environ[i][name_len] == '=')
        {
            return (ft_strdup(environ[i] + name_len + 1));
        }
        i++;
    }
    return (NULL);
}
