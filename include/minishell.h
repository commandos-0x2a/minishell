/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:15:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/08 07:12:21 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stddef.h>
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

# define NAME "minishell"

# define HOSTNAME_MAX 64
# define USERNAME_MAX 32
# define PATH_MAX_LEN 3000
# define PROMPT_MAX (HOSTNAME_MAX + USERNAME_MAX + PATH_MAX_LEN + 10)

# define PROMPT "commandos0x2a$ "

// Environment functions
int     ft_setenv(const char *name, const char *value, int overwrite);
int     ft_putenv(char *string);
int     ft_test(char **argv);

// Terminal configuration
char    *get_prompt(void);
void    handle_line(char *line);
void    cleanup_shell(void);

// tokens and exec
char	**tokenizer(char *s, int i);
void	print_tokenizer(char *line, int indent);
char	*expand_str(char *str);
void	argv_expander(char **argv);
char	*get_argv0(char **tokens);


// libft function
size_t	ft_join_path(char *dest, const char *path1, const char *path2);
int		get_full_path(char *full_path, char **argv, char *command);
char	*ft_getenv(const char *name);

// Built-in commands
int		ft_cd(char **argv);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(char **argv);
int		ft_exit(char **argv);
int		handle_builtin(char **argv);

void    restore_output(int original_fd);


char	**redirection_handler(char **tokens, int _dup, int *status);
int 	exec_command(char **tokens, int in_fd, int *out_fd, int is_pipe);
int		executioner(char **tokens);
int		flow_control(char *chain);


char **handle_wildcards(char **argv);



// Add these prototypes
int handle_subshell(char * cmd,int indent);
int is_parent_builtin(char *cmd);


int	here_doc(char *limiter);

#endif
