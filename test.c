#include "minishell.h"

static void	swap(t_list *t, t_list *t1)
{
}

int	main(void)
{
	t_list	*t;
	t_list	*m;

	t = 0;
	for (int i = 0; i < 6; i++)
		ft_lstadd_back(&t, ft_lstnew(ft_itoa(i), 0, 0));
	m = t;
	for (int i = 0; m; i++)
	{
		printf("i ==%s \n", m->cmd);
		m = m->next;
	}
	swap(&t, &t->next);
	for (int i = 0; t; i++)
	{
		printf("i ==>%s \n", t->cmd);
		t = t->next;
	}
}
