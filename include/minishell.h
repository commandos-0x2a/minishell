/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:15:08 by yaltayeh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/04 21:22:01 by mkurkar          ###   ########.fr       */
=======
/*   Updated: 2025/01/04 21:13:04 by yaltayeh         ###   ########.fr       */
>>>>>>> refs/remotes/origin/dev
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif


# include <readline/readline.h>
# include <readline/history.h>


# define HOSTNAME_MAX 64
# define USERNAME_MAX 32
# define PATH_MAX_LEN 3000
# define PROMPT_MAX (HOSTNAME_MAX + USERNAME_MAX + PATH_MAX_LEN + 10)

# define PROMPT "commandos0x2a$ "


char    *get_prompt(void);
void    handle_line(char *line);
void    cleanup_shell(void);



char	*ft_getenv(const char *name);

char	**tokenizer(char *s, int i);
size_t	ft_join_path(char *dest, const char *path1, const char *path2);
int		get_full_path(char *full_path, char **argv, char *command);
void	print_tokenizer(char *line, int indent);


pid_t	run_here_doc_process(char *limiter, int *out_fd);

// Built-in commands
int		ft_cd(char **argv);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(char **argv);
int		ft_exit(char **argv);
int		is_builtin(char *cmd);
int		handle_builtin(char **argv);

#endif
