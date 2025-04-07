/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:02:40 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/03 23:24:20 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include <stdlib.h>

#define PREFIX "minishell: "


# define PRINT_ERRNO \
	ft_fprintf(2, PREFIX"%s: %s\n", __func__, strerror(errno))

# define PRINT_ALLOCATE_ERROR PRINT_ERRNO

# define PRINT_FILE_ERROR(filename) \
	ft_fprintf(2, PREFIX"%s: %s\n", filename, strerror(errno))

# define PRINT_SYSCALL_ERROR PRINT_ERRNO
	
	


// libft function
size_t	ft_join_path(char *dest, const char *path1, const char *path2);
int		get_full_path(char full_path[PATH_MAX], char *cmd);
char	*ft_getenv(const char *name);
int		ft_setenv(const char *name, const char *value, int overwrite);
int		ft_free_array_str(char **ptr);
char	**ft_tokpbrk(char **tokens, const char *strset, ...);
char	**ft_split(const char *s, char *d);

char	**copy_dptr(char **dptr);
void	free_dptr(char **ptr);

#endif