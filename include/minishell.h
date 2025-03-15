/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:15:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/15 21:41:03 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <libft.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#ifdef __linux__
#include <linux/limits.h>
// #  include <bits/termios-c_lflag.h>
// #  include <asm-generic/termbits.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>
#else
#include <limits.h>
#endif

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <termios.h>
#include <signal.h>

#include "minishell_utils.h"

#define PREFIX "minishell: "

#define HOSTNAME_MAX 64
#define USERNAME_MAX 32
#define PATH_MAX_LEN 3000
#define PROMPT_MAX (HOSTNAME_MAX + USERNAME_MAX + PATH_MAX_LEN + 10)

#define DEFAULT_PROMPT "0x2a$ "

// Define maximum sizes for config values
#define MAX_PROMPT_STYLE 32
#define MAX_CONFIG_LINE 256

// Add these color definitions before the structs
# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

typedef struct s_tokens
{
	char	**tokens;
	int		nb_tokens;
	int		nb_heredoc;
	int		*heredoc_fds;
	int		i;
}	t_tokens;


// Terminal configuration
char *get_prompt(void);
void handle_line(char *line);
void cleanup_shell(void);

/*  tokenizer  */
void		print_tokenizer(char *line, int indent);
t_tokens	tokenizer(char *s);
char		*get_argv0(char **tokens);
char		**get_argv(char **tokens);
void		free_tokens(t_tokens *tok);


/*  expander  */
char	*expand_str(char *str);
char	*expand_str_no_quote(char *str);
char	**argv_expander(char **argv);

/*  wildcarda  */
char **handle_wildcards(char **argv);

/*  execution  */
# define IS_PIPE		0b01
# define IS_PREV_PIPE	0b10
# define IS_PIPE_MASK	0b11

int	redirection_handler(char **tokens, int here_doc_fd, int change_std);
int	command_execution(t_tokens *tok, char **tokens, \
						int *fd,\
						int is_pipe);
int	pipeline_control(t_tokens *tok, char **pipeline);
int	flow_control(char *line);
int	flow_check_syntax(char **tokens);
int	wait_children(int target_pid);
int	*run_all_heredoc(char **tokens, int nb_pipeline);

/*  Built-in commands  */
int		handle_builtin(t_tokens *tok, char **argv, int _exit);
int		is_builtin(char *cmd);
int		ft_cd(char **argv);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(char **argv);
int		ft_exit(char **argv, int *_exit);
int		ft_test(char **argv);
int		ft_export(char **argv);
int		ft_unset(char **argv);

// Modify config structure to use fixed arrays
typedef struct s_config
{
	char prompt_style[MAX_PROMPT_STYLE];
	int color_enabled;
} t_config;

// Modify prototypes
void load_config(t_config *config);
void save_config(const t_config *config);

void setup_signals(void);
void reset_signals(void);

// Environment management functions
char ***__init__env(void);
char **create_env_copy(void);
void cleanup_env_copy(void);

// Add color function prototype
void print_color(char *color, char *str);

// void set_signals_child(void);

// Add global variable declaration and new function prototypes
int *heredoc_active(void);

void save_signal_handlers(void);
void restore_signal_handlers(void);

// Add this struct and function prototype
struct s_sig_handlers
{
	struct sigaction old_int;
	struct sigaction old_quit;
};

struct s_sig_handlers *get_sig_handlers(void);

#endif
