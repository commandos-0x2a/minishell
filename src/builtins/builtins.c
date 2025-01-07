/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/07 17:12:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Regular built-ins can run in child process (output only)
* Shell built-ins must run in parent process (modify shell state)
*/
int is_builtin(char *cmd)
{
    int type;

    if (!cmd)
        return (0);

    type = 0;
    if (ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "env") == 0)
        type |= 1;
    if (ft_strcmp(cmd, "cd") == 0 || 
            ft_strcmp(cmd, "exit") == 0)
		type |= 2;
    if (ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0)
		type |= 3;
    return (type);
}

int handle_builtin(char **argv)
{
    int ret;

    argv = redirection_handler(argv, 0, &ret);
    if (ret != 0)
        return (ret);
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
