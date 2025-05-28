/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:48:06 by mkurkar           #+#    #+#             */
/*   Updated: 2025/05/28 19:58:50 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	increment_shlvl(t_mini *mini)
{
    char	*shlvl_str;
    char	*shlvl_value;
    char	*new_shlvl_str;
    int		shlvl;

    shlvl_str = ft_getenv(mini->env, "SHLVL");
    if (!shlvl_str)
    {
        new_shlvl_str = make_env_variable("SHLVL", "1");
        if (!new_shlvl_str)
            return (1);
        update_env(&mini->env, new_shlvl_str);
        free(new_shlvl_str);
        return (0);
    }
    shlvl = ft_atoi(shlvl_str) + 1;
    free(shlvl_str);
    shlvl_value = ft_itoa(shlvl, 0);
    new_shlvl_str = make_env_variable("SHLVL", shlvl_value);
    if (!new_shlvl_str)
    {
        free(shlvl_value);
        return (1);
    }
    free(shlvl_value);
    update_env(&mini->env, new_shlvl_str);
    free(new_shlvl_str);
    return (0);
}