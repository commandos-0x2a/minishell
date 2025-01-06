/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/05 21:58:43 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            // ft_strcmp(cmd, "export") == 0 ||
            // ft_strcmp(cmd, "unset") == 0 ||
			ft_strcmp(cmd, "test") == 0);
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
    // if (ft_strcmp(argv[0], "export") == 0)
    //     return (ft_export(argv));
    // if (ft_strcmp(argv[0], "unset") == 0)
    //     return (ft_unset(argv));
    if (ft_strcmp(argv[0], "test") == 0)
        return (ft_test(argv));
    return (1);
}
