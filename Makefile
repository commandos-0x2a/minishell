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
			builtins/test			\
			builtins/unset			\
			utils/dptr				\
			utils/ft_getenv			\
			utils/ft_setenv			\
			utils/get_full_path		\
			utils/ft_list			\
			signals					\
			wait_children			\
			get_argv				\
 			pipeline_control		\
			redirection_handler		\
			tokenizer				\
			heredoc					\
#
M_FILES =	mandatory/main						\
			mandatory/execute_complex_command	\
			mandatory/execute_simple_command	\
			mandatory/check_syntax				\
			mandatory/expand_line				\
			mandatory/expander					\
#
B_FILES =	bonus/main						\
			bonus/execute_complex_command	\
			bonus/execute_simple_command	\
			bonus/check_syntax				\
			bonus/expand_line				\
			bonus/expander					\
			bonus/expand_wildcard			\
 			bonus/flow_control				\
			bonus/subshell					\
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
