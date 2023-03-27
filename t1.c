
#include "src/minishell.h"

int	main(void)
{
	execve("/bin/cat", {"cat", "-e"})
}