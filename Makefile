NAME		= minishell_mad
NAME_BONUS	= minishell

CC			= cc
LDFLAGS		= -L./libft -lft -lreadline -lncurses
CFLAGS		= -Wall -Wextra -Werror -g
CPPFLAGS	= -I./libft/include -I./include

SRCDIR = src
OBJDIR = build

FILES = builtins/builtins			\
			builtins/cd				\
			builtins/echo			\
			builtins/env			\
			builtins/exit			\
			builtins/export			\
			builtins/pwd			\
			builtins/test			\
			builtins/unset			\
			utils/config			\
			utils/dptr				\
			utils/ft_getenv			\
			utils/ft_join_path		\
			utils/ft_setenv			\
			utils/get_full_path		\
			utils/readline_handler	\
			utils/ft_tokpbrk		\
			utils/ft_split			\
			utils/signals			\
			utils/clean_and_exit	\
			str_expander			\
			wait_children			\
			here_doc				\
			get_argv				\
			get_argv0				\
			add_space_to_line		\
#

BONUS_FILES = main							\
			execution/command_execution		\
			execution/run_command			\
			execution/flow_control			\
			execution/pipeline_control		\
			execution/redirection_handler	\
			wildcard						\
			print_tokenizer					\
			tokenizer						\
#

MANDATORY_FILES = 

#

OBJECTS 			= $(FILES:%=$(OBJDIR)/%.o)
MANDATORY_OBJECTS	= $(MANDATORY_FILES:%=$(OBJDIR)/mandatory/%.o)
BONUS_OBJECTS 		= $(BONUS_FILES:%=$(OBJDIR)/bonus/%.o)


# all: libft $(NAME)

all: libft $(NAME_BONUS)

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJECTS) $(MANDATORY_OBJECTS) libft/libft.a
	$(CC) $(OBJECTS) $(MANDATORY_OBJECTS) $(LDFLAGS) -o $@

$(NAME_BONUS): $(OBJECTS) $(BONUS_OBJECTS) libft/libft.a
	$(CC) $(OBJECTS) $(BONUS_OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
#	$(MAKE) -C libft clean
	rm -f $(OBJECTS) $(MANDATORY_OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus libft clean fclean re
