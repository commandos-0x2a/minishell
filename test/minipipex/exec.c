#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

char	**ft_split(const char *s, char *d);

void	free_dptr(char **ptr)
{
	char	**_ptr;

	_ptr = ptr;
	while (*_ptr)
		free(*_ptr++);
	free(ptr);
}

int	get_full_path(char full_path[PATH_MAX], char *cmd)
{
	char	*path_env;
	char	**paths;
	int		i;
	
	if (strncmp(cmd, "./", 2) == 0 
		|| strncmp(cmd, "../", 3) == 0
		|| strncmp(cmd, "/", 1) == 0)
	{
		if (strlcpy(full_path, cmd, SIZE_MAX) >= SIZE_MAX)
		{
			errno = ENAMETOOLONG;
			return (1);
		}
		return (0);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (1);
	paths = ft_split(path_env, ":");
	if (!paths)
		return (1);
	i = 0;
	while (paths[i])
	{
		if (strlcpy(full_path, paths[i], SIZE_MAX) < SIZE_MAX
			&& strlcat(full_path, "/", SIZE_MAX) < SIZE_MAX
			&& strlcat(full_path, cmd, SIZE_MAX) < SIZE_MAX
			&& access(full_path, X_OK) == 0)
			{
				free_dptr(paths);
				return (0);
			}
		i++;
	}
	free_dptr(paths);
	return (1);
}

void	run_command(char *command)
{
	char	**argv;
	char	full_path[PATH_MAX];

	argv = ft_split(command, " ");
	if (get_full_path(full_path, argv[0]))
		exit(1);
	
	execve(full_path, argv, NULL);
}

int with_pipe(char *cmd1, char *cmd2)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (1);

	if (fork() == 0)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fds[1]);
		
		run_command(cmd1);
		exit(1);
	}
	if (fork() == 0)
	{
		close(pipe_fds[1]);
		if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
			exit(1);
		close(pipe_fds[0]);
		run_command(cmd2);
		exit(1);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	while (wait(NULL) != -1)
		;
	return (0);
}

int with_file(char *cmd1, char *cmd2)
{
	int	fd;
	char filename[] = "pipe";

	if (fork() == 0)
	{
		if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
			exit(1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit(1);
		
		run_command(cmd1);
		exit(1);
	}
	if (fork() == 0)
	{
		if ((fd = open(filename, O_RDONLY | O_TRUNC | O_CREAT, 0644)) == -1)
			exit(1);
		if (dup2(fd, STDIN_FILENO) == -1)
			exit(1);

		run_command(cmd2);
		exit(1);
	}
	while (wait(NULL) != -1)
		;
	unlink(filename);
	return (0);
}

