/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:26 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/11 18:47:07 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static void get_config_path(char *path_buf)
{
	char *home;

	home = ft_getenv("HOME");
	if (!home)
	{
		path_buf[0] = '\0';
		return;
	}
	ft_strlcpy(path_buf, home, PATH_MAX);
	ft_strlcat(path_buf, "/.2arc", PATH_MAX);
}

static void set_default_config(t_config *config)
{
	ft_strlcpy(config->prompt_style, "default", MAX_PROMPT_STYLE);
	config->color_enabled = 1;
}

static void parse_config_line(char *line, t_config *config)
{
	char key[MAX_CONFIG_LINE];
	char value[MAX_CONFIG_LINE];
	char *equals;
	size_t key_len;

	// Skip whitespace and comments
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '#' || *line == '\0')
		return;

	// Find equals sign
	equals = ft_strchr(line, '=');
	if (!equals)
		return;

	// Extract key
	key_len = equals - line;
	if (key_len >= MAX_CONFIG_LINE)
		key_len = MAX_CONFIG_LINE - 1;
	ft_strlcpy(key, line, key_len + 1);

	// Skip equals and whitespace
	equals++;
	while (*equals == ' ' || *equals == '\t')
		equals++;

	// Extract value
	ft_strlcpy(value, equals, MAX_CONFIG_LINE);

	// Remove trailing whitespace
	key_len = ft_strlen(key);
	while (key_len > 0 && (key[key_len - 1] == ' ' || key[key_len - 1] == '\t'))
		key[--key_len] = '\0';

	// Set config values
	if (ft_strcmp(key, "PROMPT_STYLE") == 0)
		ft_strlcpy(config->prompt_style, value, MAX_PROMPT_STYLE);
	else if (ft_strcmp(key, "COLOR_ENABLED") == 0)
		config->color_enabled = ft_atoi(value);
}

void load_config(t_config *config)
{
	char path[PATH_MAX];
	char line[MAX_CONFIG_LINE];
	int fd;
	ssize_t bytes_read;
	size_t pos;

	set_default_config(config);
	get_config_path(path);
	if (!path[0])
		return;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return;

	pos = 0;
	while ((bytes_read = read(fd, &line[pos], 1)) > 0)
	{
		if (line[pos] == '\n' || pos == MAX_CONFIG_LINE - 1)
		{
			line[pos] = '\0';
			parse_config_line(line, config);
			pos = 0;
		}
		else
			pos++;
	}

	close(fd);
}

void save_config(const t_config *config)
{
	char path[PATH_MAX];
	int fd;

	get_config_path(path);
	if (!path[0])
		return;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return;

	ft_fprintf(fd, "# Terminal Configuration\n");
	ft_fprintf(fd, "PROMPT_STYLE=%s\n", config->prompt_style);
	ft_fprintf(fd, "COLOR_ENABLED=%d\n", config->color_enabled);

	close(fd);
}
