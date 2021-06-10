#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "pipex.h"

extern char **(environ);

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

void	spawn(t_pair pair, int fdclose, char *cmd, char **path)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		dup2(pair.out, 1);
		dup2(pair.in, 0);
		close(pair.out);
		close(pair.in);
		close(fdclose);
		prep_exec(cmd, path);
	}
	else if (pid < 0)
		panic();
	close(pair.in);
	close(pair.out);
}

void	pipeline(int ac, char **av, char **path)
{
	int		i;
	int		fd;
	int		out;
	int		fds[2];

	fd = panic_open(av[1], O_RDONLY | O_CLOEXEC);
	i = 2;
	while (i < ac - 2)
	{
		pipe(fds);
		spawn((t_pair){fd, fds[1]}, fds[0], av[i], path);
		fd = fds[0];
		i++;
	}
	out = create_file(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (out < 0)
		close(fd);
	else
		spawn((t_pair){fd, out}, fds[1], av[i], path);
}

int	main(int ac, char **av)
{
	int		pid;
	char	**path;

	if (ac < 5)
		exit(1);
	path = ft_split(find_path(), ':');
	if (!path)
		panic();
	pipeline(ac, av, path);
	while (wait(NULL) > 0)
		(void)((void)"norme bullshit %d", pid);
	exit(0);
}
