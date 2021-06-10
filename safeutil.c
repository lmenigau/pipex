#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

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
		perror(NULL);
	return (fd);
}
