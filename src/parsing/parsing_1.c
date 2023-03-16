/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
/*   Updated: 2023/03/16 12:43:47 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

void	fill_cmds(char *s, t_env *env)
{
	char	**c;
	int		i;

	c = ft_split(add_spc(s, 0, 0, '<'), '|');
	i = 0;
	while (c && c[i])
		ft_lstadd_back(&g_v, ft_lstnew(c[i++], env));
	free(c[i]);
	free(c);
}

void	ft_lstadd_back1(t_list **lst, t_list *new)
{
	t_list	*t;

	t = *lst;
	if (new &&lst)
	{
		if (*lst)
		{
			t = *lst;
			while (t->next != NULL)
				t = t->next;
			t->next = new;
		}
		else
			*lst = new;
	}
}

int	main(int ac, char **av, char **ev)
{
	t_env	*env;
	t_env	*j;
	t_list	*tem;

	//char	*s;
	(void)ac;
	(void)av;
	env = 0;
	env = getlstenv(ev);
	j = env;
	// while (1)
	// {
	// 	g_v = 0;
	// 	s = readline("\033[0;32mMINISHELL#(*_*)|\033[36;01m❯❯❯❯\033[0m");
	// 	if (!s || !check_in(s))
	// 		continue ;
	// 	fill_cmds(s, env);
	// 	tem = g_v;
	// 	while (g_v)
	// 	{
	// 		printf("%s\n", g_v->cmd);
	// 		g_v = g_v->next;
	// 	}
	// 	//m = expend(env, s, 0);
	// 	// print(0, 33, s);
	// 	// free(s);
	// }
	tem = ft_lstnew("1", 0);
	tem->next = ft_lstnew("2", 0);
	tem->next->next = ft_lstnew("3", 0);
	ft_lstadd_back(&tem, ft_lstnew("4", 0));
	while (tem)
	{
		printf("cmd %s\n", tem->cmd);
		tem = tem->next;
	}
}
