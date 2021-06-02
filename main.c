#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

void	panic(void)
{
	perror(NULL);
	exit(1);
}

int		main(int ac, char **av)
{
	int		fds[2];
	int		io[2];

	if (ac != 5)
		exit(1);
	printf("%d\n", PATH_MAX);
	io[0] = open(av[1], O_RDONLY);
	if (io[0] < 0)
		panic();
	io[1] = open(av[4], O_CREAT | O_WRONLY);
	if (io[1] < 0)
		panic();
	pipe(fds);
}
