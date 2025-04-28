NAME		= minishell
B_NAME		= minishell_bonus

CC			= cc
LDFLAGS		= -L./libft -lft -lreadline -lncurses
CFLAGS		= -Wall -Wextra -Werror -g
CPPFLAGS	= -I./libft/include -I./include

SRCDIR = src
OBJDIR = build

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG
endif

FILES = builtins/builtins			\
			builtins/cd				\
			builtins/echo			\
			builtins/env			\
			builtins/exit			\
			builtins/export			\
			builtins/pwd			\
			builtins/unset			\
			utils/dptr				\
			utils/ft_getenv			\
			utils/get_full_path		\
			utils/ft_list			\
			utils/print_error		\
			utils/tty				\
			signals					\
			wait_children			\
			get_argv				\
 			pipeline_control		\
			redirection_handler		\
			tokenizer				\
			heredoc					\
			main					\
			expand_env				\
			expand_str				\
#
M_FILES =	mandatory/execute_complex_command	\
			mandatory/execute_simple_command	\
			mandatory/check_syntax				\
			mandatory/expand_line				\
			mandatory/expand_tokens				\
			mandatory/cut_slice					\
#
B_FILES =	bonus/execute_complex_command	\
			bonus/execute_simple_command	\
			bonus/check_syntax				\
			bonus/expand_line				\
			bonus/expand_tokens				\
			bonus/expand_wildcard			\
 			bonus/flow_control				\
			bonus/subshell					\
			bonus/cut_slice					\

#

OBJECTS = $(FILES:%=$(OBJDIR)/%.o)
M_OBJECTS = $(M_FILES:%=$(OBJDIR)/%.o)
B_OBJECTS = $(B_FILES:%=$(OBJDIR)/%.o)

all: libft $(NAME)

bonus: libft $(B_NAME)

libft:
	@$(MAKE) -C libft

$(NAME): $(M_OBJECTS) $(OBJECTS) libft/libft.a
	$(CC) $(M_OBJECTS) $(OBJECTS) $(LDFLAGS) -o $@

$(B_NAME): $(B_OBJECTS) $(OBJECTS) libft/libft.a
	$(CC) $(B_OBJECTS) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
#	$(MAKE) -C libft clean
	rm -f $(M_OBJECTS) $(OBJECTS) $(B_OBJECTS)

fclean: clean
	rm -f $(NAME) $(B_NAME)

re: fclean all

.PHONY: all libft clean fclean re
