NAME	= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
SRCDIR		= src
OBJDIR		= build
CPPFLAGS	+= -I./include

FILES =	\
		ft_string/ft_isalnum		\
		ft_string/ft_isascii		\
		ft_string/ft_isalpha		\
		ft_string/ft_isdigit		\
		ft_string/ft_isprint		\
		ft_string/ft_isspace		\
		ft_string/ft_itoa			\
		ft_string/ft_itoa_base		\
		ft_string/ft_strchr			\
		ft_string/ft_strdup			\
		ft_string/ft_striteri		\
		ft_string/ft_strjoin		\
		ft_string/ft_strlcat		\
		ft_string/ft_strlcpy		\
		ft_string/ft_strlen	 		\
		ft_string/ft_strmapi		\
		ft_string/ft_strncmp		\
		ft_string/ft_strcmp			\
		ft_string/ft_strnstr		\
		ft_string/ft_strrchr		\
		ft_string/ft_strtrim		\
		ft_string/ft_substr			\
		ft_string/ft_tolower		\
		ft_string/ft_toupper		\
		ft_string/ft_strtok			\
		ft_string/ft_atoi			\
		ft_string/ft_atou			\
		ft_string/ft_str_is_numeric	\
		\
		ft_memory/ft_bzero			\
		ft_memory/ft_memset			\
		ft_memory/ft_memcpy			\
		ft_memory/ft_memmove		\
		ft_memory/ft_memchr			\
		ft_memory/ft_memcmp			\
		ft_memory/ft_calloc			\
		\
		ft_io/ft_putchar			\
		ft_io/ft_putstr				\
		ft_io/ft_putchar_fd			\
		ft_io/ft_putstr_fd			\
		ft_io/ft_putendl_fd			\
		ft_io/ft_putnbr_fd			\
		ft_io/ft_putbase_fd			\
		\
		ft_printf/ft_printf						\
		ft_printf/ft_fprintf					\
		ft_printf/ft_snprintf					\
		ft_printf/ft_vprintf					\
		ft_printf/ft_vfprintf					\
		ft_printf/ft_vsnprintf					\
#

OBJECTS	= $(FILES:%=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $?

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)

re: clean all

.PHONY: all clean re
