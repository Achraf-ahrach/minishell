#include "src/minishell.h"
#include "src/libft/libft.h"
#include <string.h>

int	main(int ac, char **av, char **ev)
{
	int id;
	int p[2];

	pipe(p);
	id = fork();
	if (!id)
		ft_putstr_fd("hello fomr here\n",p[1]);
	else
	{
		printf("fgjfgjflgjdfklgjfklgj\n");
	wait(0);
	close(p[1]);
	dup2(p[0] , 0);
	execve("/bin/cat", &av[1], ev);
	}
	
}