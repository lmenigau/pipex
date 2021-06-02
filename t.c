#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
	execve(av[1], av, NULL);
	perror(NULL);
}
