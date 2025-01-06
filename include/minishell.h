/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:15:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/06 17:44:34 by yaltayeh         ###   ########.fr       */
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
int		executioner(char *line, int indent);
void	print_tokenizer(char *line, int indent);
pid_t	run_here_doc_process(char *limiter, int *out_fd);
void	argv_expander(char **argv);

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
int		is_builtin(char *cmd);
int		handle_builtin(char **argv);

int     setup_redirections(char **argv);
void    restore_output(int original_fd);


int	here_doc(char *limiter);

int	in_redirection(char *infile);

int	out_append(char *outfile);



int	out_redirection(char *outfile);
int	check_pipe(char ***argv_p);
int	exec_command(char ***argv_p, int in_fd, int *out_fd);
// int	executioner(char *line, int indent);

char **handle_wildcards(char **argv);


int exec_command(char ***argv_p, int in_fd, int *out_fd);
int executioner(char *line, int indent);


#endif
