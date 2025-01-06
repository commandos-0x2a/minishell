/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/06 15:20:09 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Regular built-ins can run in child process (output only)
* Shell built-ins must run in parent process (modify shell state)
*/
int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "cd") == 0 || 
            ft_strcmp(cmd, "exit") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0);
}

int handle_builtin(char **argv)
{
    int ret;

    ret = 1;
    if (ft_strcmp(argv[0], "echo") == 0)
        ret = ft_echo(argv);
    else if (ft_strcmp(argv[0], "pwd") == 0)
        ret = ft_pwd(argv);
    else if (ft_strcmp(argv[0], "env") == 0)
        ret = ft_env(argv);
    else if (ft_strcmp(argv[0], "cd") == 0)
        ret = ft_cd(argv);
    else if (ft_strcmp(argv[0], "exit") == 0)
        ret = ft_exit(argv);
    return (ret);
}
