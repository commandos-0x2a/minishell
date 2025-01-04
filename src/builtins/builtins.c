/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/04 21:22:01 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 || 
            ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}

int handle_builtin(char **argv)
{
    if (ft_strcmp(argv[0], "cd") == 0)
        return (ft_cd(argv));
    if (ft_strcmp(argv[0], "echo") == 0)
        return (ft_echo(argv));
    if (ft_strcmp(argv[0], "pwd") == 0)
        return (ft_pwd(argv));
    if (ft_strcmp(argv[0], "env") == 0)
        return (ft_env(argv));
    if (ft_strcmp(argv[0], "exit") == 0)
        return (ft_exit(argv));
    return (1);
}
