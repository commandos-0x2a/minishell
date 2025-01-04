# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    include.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 00:46:54 by yaltayeh          #+#    #+#              #
#    Updated: 2025/01/04 21:30:00 by mkurkar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# If LIBFTDIR not define set '.',
# else Set before include,
# because include libft from anywhere
LIBFTDIR ?= .

# Set colors variables
RESET	= \033[0;39m
RED		= \033[0;91m
GREEN	= \033[0;92m
MAGENTA	= \033[0;95m
YELLOW	= \033[0;93m

# Set dirs path and set 
LIBFT_SRCDIR	 = $(LIBFTDIR)/src
LIBFT_BUILDDIR	 = $(LIBFTDIR)/build
INCLUDE 		+= -I$(LIBFTDIR)/include

# Set final target path
LIBFT = $(LIBFTDIR)/libft.a

# Set all source files to LIBFT_SOURCES
LIBFT_SOURCES =	\
		ft_string/ft_isalnum.c			\
		ft_string/ft_isascii.c			\
		ft_string/ft_isalpha.c			\
		ft_string/ft_isdigit.c			\
		ft_string/ft_isprint.c			\
		ft_string/ft_isspace.c			\
		ft_string/ft_itoa.c				\
		ft_string/ft_itoa_base.c		\
		ft_string/ft_strchr.c			\
		ft_string/ft_strdup.c			\
		ft_string/ft_striteri.c			\
		ft_string/ft_strjoin.c			\
		ft_string/ft_strlcat.c			\
		ft_string/ft_strlcpy.c			\
		ft_string/ft_strlen.c	 		\
		ft_string/ft_strmapi.c			\
		ft_string/ft_strncmp.c			\
		ft_string/ft_strcmp.c			\
		ft_string/ft_strnstr.c			\
		ft_string/ft_strrchr.c			\
		ft_string/ft_strtrim.c			\
		ft_string/ft_substr.c			\
		ft_string/ft_tolower.c			\
		ft_string/ft_toupper.c			\
		ft_string/ft_strtok.c			\
		ft_string/ft_atoi.c				\
		ft_string/ft_atou.c				\
		ft_string/ft_str_is_numeric.c	\

LIBFT_SOURCES +=	\
		ft_memory/ft_bzero.c			\
		ft_memory/ft_memset.c			\
		ft_memory/ft_memcpy.c			\
		ft_memory/ft_memmove.c			\
		ft_memory/ft_memchr.c			\
		ft_memory/ft_memcmp.c			\
		ft_memory/ft_calloc.c

LIBFT_SOURCES +=	\
		ft_io/ft_putchar.c				\
		ft_io/ft_putstr.c				\
		ft_io/ft_putchar_fd.c			\
		ft_io/ft_putstr_fd.c			\
		ft_io/ft_putendl_fd.c			\
		ft_io/ft_putnbr_fd.c			\
		ft_io/ft_putbase_fd.c

LIBFT_SOURCES += \
		ft_printf/ft_printf.c					\
		ft_printf/ft_fprintf.c					\
		ft_printf/ft_vprintf.c					\
		ft_printf/ft_vfprintf.c					\
		ft_printf/ft_snprintf.c					\
		ft_printf/utils/ft_printf_redirect.c	\
		ft_printf/utils/ft_flags_parser.c		\
		ft_printf/utils/ft_handlers.c			\
		ft_printf/utils/ft_handlers2.c			\
		ft_printf/utils/ft_decimal_handler.c	\
		ft_printf/utils/ft_u_decimal_handler.c	\
		ft_printf/utils/ft_flags_apply.c

LIBFT_SOURCES += \
		get_next_line/get_next_line.c		\
		get_next_line/get_next_line_utils.c	\

LIBFT_SOURCES += \
		ft_stack/ft_init_node.c				\
		ft_stack/ft_init_stack.c			\
		ft_stack/ft_stack_size.c			\
											\
		ft_stack/ft_stack_head_pop.c		\
		ft_stack/ft_stack_head_push.c		\
		ft_stack/ft_stack_head_iter.c		\
											\
		ft_stack/ft_stack_tail_push.c		\
		ft_stack/ft_stack_tail_pop.c		\
		ft_stack/ft_stack_tail_iter.c		\
											\
		ft_stack/ft_cmp_node.c				\
		ft_stack/ft_stack_fn_caller.c		\
		ft_stack/ft_stack_copy_reverse.c	\
		ft_stack/ft_stack_copy.c			\
		ft_stack/ft_stack_mapi.c			\
											\
		ft_stack/ft_stack_search.c			\
											\
		ft_stack/ft_stack_delnode.c			\
		ft_stack/ft_stack_clear.c			\

#

# Convert all source files names from .c to .o
LIBFT_OBJECTS  := $(LIBFT_SOURCES:.c=.o)

# Add build dir before all object files
LIBFT_OBJECTS := $(addprefix $(LIBFT_BUILDDIR)/, $(LIBFT_OBJECTS))

# Add soucre dir before all source files
LIBFT_SOURCES := $(addprefix $(LIBFT_SRCDIR)/, $(LIBFT_SOURCES))

# Add all libft source file to OBJECTS
SOURCES += $(LIBFT_SOURCES)
# Add all libft object file to SOURCES
OBJECTS += $(LIBFT_OBJECTS)

# Build object(.o) file from source(.c) file
# and dir if not exists
$(LIBFT_BUILDDIR)/%.o: $(LIBFT_SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@ \
		&& echo "$(GREEN)Build $@ object from $< $(RESET)"\
		|| echo "$(RED)Error in try build $< $(RESET)"
