#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	write(1, "lol", strlen("lol"));
}
