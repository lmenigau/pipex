#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include "pipex.h"
#include <string.h>

extern char **(environ);

void	panic(void)
{
	perror(NULL);
	exit(1);
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
	char 	*str;
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
	printf("%s\n", "command not found");
}

int	main(int ac, char **av)
{
	int		fds[2];
	int		io[2];
	char 	**path;

	if (ac < 5)
		exit(1);
	path = ft_split(find_path(), ':');
	if (!path)
		panic();
	pipe(fds);
	if (!fork())
	{
		io[0] = open(av[1], O_RDONLY);
		if (io[0] < 0)
			panic();
		dup2(io[0], 0);
		dup2(fds[0], 1);
		prep_exec(av[2], path);
	}
	io[1] = open(av[4], O_CREAT | O_WRONLY);
	if (io[1] < 0)
		panic();
}
