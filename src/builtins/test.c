/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:26:15 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/05 18:29:27 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_test(char **argv)
{
    extern char **environ;
    char *value;
    int i = 0;

    (void)argv;
	ft_setenv("MY_VAR", "my_value", 1);
    value = ft_getenv("MY_VAR");
    ft_fprintf(2, "Current MY_VAR=%s\n", value ? value : "(null)");
    free(value); 
    while (environ[i])
    {
        if (ft_strncmp(environ[i], "MY_VAR=", 7) == 0)
        {
            ft_fprintf(2, "Found in environ: %s\n", environ[i]);
            break;
        }
        i++;
    }
    return (0);
}
