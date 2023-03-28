#include "src/minishell.h"
#include <string.h>

int	main(int ac, char **av, char **ev)
{
	int fd = open("ls", O_RDONLY, 777);
	printf("fd:%d\n", fd);

	dup2(fd, 0);
	if (!fork())
		execve("/bin/cat", &av[1], ev);
	wait(0);
	close(fd);
	fd = open("ls", O_RDONLY | O_WRONLY, 777);
	write(fd, "hello\n", strlen("hello\n"));
	//printf("fd:%d\n", fd);
}