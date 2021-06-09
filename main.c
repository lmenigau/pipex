#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include "pipex.h"
#include <string.h>
#include <sys/types.h>

extern char **(environ);

void	panic(void)
{
	perror(NULL);
	exit(1);
}

int	panic_open(char *path, int flags)
{
	int	fd;

	fd = open(path, flags);
	if (fd < 0)
		panic();
	return (fd);
}

int	create_file(char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd < 0)
		panic();
	return (fd);
}

char	*find_path(void)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp("PATH=", environ[i], 5))
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

void	prep_exec(char *cmd, char **path)
{
	int		i;
	char	**cmda;
	char	*str;
	char	*tmp;

	i = 0;
	cmda = ft_split(cmd, ' ');
	if (!cmda)
		panic();
	while (path[i])
	{
		tmp = ft_strjoin("/", cmda[0]);
		str = ft_strjoin(path[i], tmp);
		free(tmp);
		execve(str, cmda, environ);
		free(str);
		i++;
	}
	panic();
}

void	redirect(t_pair pair)
{
	dup2(pair.out, 1);
	dup2(pair.in, 0);
	close(pair.out);
	close(pair.in);
}

void	spawn(t_pair pair, int fdclose, char *cmd, char **path)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		redirect(pair);
		close(fdclose);
		prep_exec(cmd, path);
	}
	else if (pid < 0)
		panic();
	close(pair.in);
	close(pair.out);
}

pid_t	wait_assign_in_control_structure(pid_t *pid)
{
	return (*pid = wait(NULL));
}

int	main(int ac, char **av)
{
	int		fds[2];
	int		fd;
	int		pid;
	char	**path;

	if (ac < 5)
		exit(1);
	path = ft_split(find_path(), ':');
	if (!path)
		panic();
	pipe(fds);
	fd = panic_open(av[1], O_RDONLY | O_CLOEXEC);
	spawn((t_pair){fd, fds[1]}, fds[0], av[2], path);
	fd = create_file(av[4], O_TRUNC | O_CREAT | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	spawn((t_pair){fds[0], fd}, fds[1], av[3], path);
	while (wait_assign_in_control_structure(&pid) > 0)
		(void)((void)"norme bullshit %d", pid);
}
