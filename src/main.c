#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	out_redirection(char *outfile)
{
	int fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(outfile);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	out_append(char *outfile)
{
	int fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(outfile);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}


void	exec_command(char **argv)
{
	char	full_path[PATH_MAX];
	extern char	**environ;
	int		i;
	char	*outfile;

	if (!argv || !argv[0])
		exit(1);

	// Handle redirections first
	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], ">>", 2) == 0)
		{
			if (ft_strlen(argv[i]) == 2)
				outfile = argv[++i];
			else
				outfile = argv[i++] + 2;
			out_append(outfile);
			argv[i - 1] = NULL;
		}
		else if (ft_strncmp(argv[i], ">", 1) == 0)
		{
			if (ft_strlen(argv[i]) == 1)
				outfile = argv[++i];
			else
				outfile = argv[i++] + 1;
			out_redirection(outfile);
			argv[i - 1] = NULL;
		}
		i++;
	}

	// Handle quotes for remaining arguments
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\'' || argv[i][0] == '\"')
		{
			size_t len = ft_strlen(argv[i]);
			if (len >= 2 && argv[i][len - 1] == argv[i][0])
			{
				argv[i][len - 1] = '\0';
				argv[i]++;
			}
		}
		i++;
	}

	int err = get_full_path(full_path, argv, "");
	if (err == 0)
	{
		execve(full_path, argv, environ);
		perror("minishell");
		exit(1);
	}
	exit(err);
}


int	executioner(char *line, int indent)
{
	char	**argv;
	int		i;
	int		pid;
	int		status;
	int		fd;

	argv = tokenizer(line, 0);
	if (!argv)
		return 0;

	// Check for built-in commands before forking
	if (argv[0] && is_builtin(argv[0]))
		return handle_builtin(argv);

	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		return (status);
	}

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '(')
		{
			argv[i][ft_strlen(argv[i]) - 1] = '\0';
			tokenizer(argv[i] + 1, indent + 4);
		}
		else
		{
			if (ft_strcmp(argv[i], "&&") == 0)
				fprintf(stderr, "%-*s%i: AND\n", indent, "", i);
			else if (ft_strcmp(argv[i], "||") == 0)
				fprintf(stderr, "%-*s%i: OR\n", indent, "", i);
			else if (ft_strncmp(argv[i], "<<", 2) == 0)
			{
				char *limiter;
				if (ft_strlen(argv[i]) == 2)
					limiter = argv[++i];
				else
					limiter = argv[i] + 2;
				pid_t proc = run_here_doc_process(limiter, &fd);
				if (proc == -1)
				{
					perror("minishell");
					exit(1);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else if (ft_strncmp(argv[i], "<", 1) == 0)
			{
				char *infile;
				if (ft_strlen(argv[i]) == 1)
					infile = argv[++i];
				else
					infile = argv[i] + 1;
				fd = open(infile, O_RDONLY);
				if (fd == -1)
					perror("minishell");
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else
			{
				exec_command(argv + i);
				fprintf(stderr, "%-*s%i: %s\n", indent, "", i, argv[i]);
			}
		}
		i++;
	}
	exit(1);
}

int main(void)
{
    char    *line;

    // atexit(cleanup_shell);
    while (1)
    {
        line = readline(get_prompt());
        if (!line)
        {
            printf("\nexit\n");
            break;
        }
        handle_line(line);
        if (*line)
            executioner(line, 0);
        free(line);
    }
    return (0);
}
