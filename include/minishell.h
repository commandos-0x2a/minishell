/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:15:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 12:35:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define __USE_XOPEN2K8
# define _GNU_SOURCE // for WUNTRACED

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
# include <sys/types.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

# define PREFIX "minishell: "

# define PRINT_ERRNO \
	ft_fprintf(2, PREFIX"%s:%d: %s\n", \
		__FILE__, __LINE__, strerror(errno))

# define PRINT_ALLOCATE_ERROR \
	ft_fprintf(2, PREFIX"%s:%d: %s\n", \
		__FILE__, __LINE__, strerror(errno))

	# define PRINT_FILE_ERROR(filename) \
	ft_fprintf(2, PREFIX"%s:%d: %s %s\n", \
		__FILE__, __LINE__, filename, strerror(errno))

# define PRINT_SYSCALL_ERROR \
	ft_fprintf(2, PREFIX"%s:%d: %s\n", \
		__FILE__, __LINE__, strerror(errno))

# define HOSTNAME_MAX 64
# define USERNAME_MAX 32
# define PROMPT_MAX (HOSTNAME_MAX + USERNAME_MAX + PATH_MAX + 10)

// Define maximum sizes for config values
# define MAX_PROMPT_STYLE 32
# define MAX_CONFIG_LINE 256

# define MAXLINE 4096

# define IS_NEXT_PIPE	0b01
# define IS_PREV_PIPE	0b10
# define pipe_mask_MASK	0b11

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_mini
{
	t_list	*tokens;
	t_list	*alias;
	t_list	*env;
	int		exit_status;
}	t_mini;

extern volatile int	g_sig;

void	mini_clean(t_mini *mini);
void	exit_handler(t_mini *mini, int exit_status);

/*  subshell  */
int		is_subshell(t_list *lst);
int		subshell_syntax(t_list *lst);
void	run_subshell(t_mini *mini);

/*  t_list  */
t_list	*lst_expand(t_list *lst, char **slices);
void	*lst_move2next(t_list **lst);
void	*lst_clean(t_list **lst);
char	**lst_2_argv(t_list **lst, int flcean);
char	**lst_2_dptr(t_list *lst);
void	lst_remove_one(t_list **lst, t_list *prev);

/*  tokenizer  */
char	*expand_line(const char *s);
t_list	*tokenizer(const char *s);

/*  argv  */
int		get_full_path(t_list *env, char full_path[PATH_MAX], char *cmd);
char	*get_argv0(t_list *lst);
void	get_argv(t_list **lst);

/*  expander  */
char	**expand_str(t_mini *mini, char *str);
char	*expand_env(t_mini *mini, char *str);
char	**expand_wildcard(char *pattern);
int		expand_tokens(t_mini *mini, t_list *lst);
t_list	*expand_tokens_2lst(t_mini *mini, const char *str);
char	*remove_qouts(char *str);

/*  execution  */
int		flow_control(t_mini *mini);
int		pipeline_control(t_mini *mini);
int		execute_complex_command(t_mini *mini, int in_fd, \
							int pipefds[2], int pipe_mask);
void	execute_simple_command(t_mini *mini);
int		check_syntax(t_list *lst);

/*  Wait children  */
int		wait_children(pid_t victim);
int		wait_child_stop(pid_t victim);

/*  redirection handling  */
int		redirection_handler(t_mini *mini, int heredoc_fd);
int		heredoc_forever(t_mini *mini, t_list *lst);

/*  environment variables  */
t_list	*copy_env_variables(void);
char	*ft_getenv(t_list *env, const char *name);

/*  built-in commands  */
int		handle_builtin(t_mini *mini, char **argv, int _exit);
int		is_builtin(t_mini *mini, const char *cmd, int expand);
int		ft_cd(t_mini *mini, char **argv);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(t_mini *mini, char **argv);
int		ft_exit(char **argv, int *_exit);
int		ft_test(t_mini *mini, char **argv);
int		ft_export(t_mini *mini, char **argv);
int		ft_unset(t_mini *mini, char **argv);

/* signal handling functions */
void	setup_signals(void);
void	setup_signals2(void);
void	reset_signals(void);

/*  utils functions  */
char	**copy_dptr(char **dptr);
void	free_dptr(char **ptr);

#endif
