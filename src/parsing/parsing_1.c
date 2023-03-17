/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
/*   Updated: 2023/03/16 20:49:32 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

void	fill_cmds(char *s, t_env *env)
{
	char	**c;
	int		i;

	printf("hello %s \n", s);
	c = ft_split1(add_spc(s, 0, 0, '<'), '|');
	i = 0;
	while (c && c[i])
	{
		ft_lstadd_back(&g_v, ft_lstnew(ft_split(c[i], ' '), env));
		printf("%s\n", c[i++]);
	}
	free(c[i]);
	free(c);
}

int	main(int ac, char **av, char **ev)
{
	char	*s;
	int		i;
	char	**m;
	t_env	*env;
	t_env	*j;
	t_list	*tem;

	//char	*s;
	(void)ac;
	(void)av;
	(void)i;
	(void)tem;
	env = 0;
	env = getlstenv(ev);
	j = env;
	m = NULL;
	i = 0;
	while (1)
	{
		g_v = 0;
		s = readline("\033[0;32mMINISHELL#(*_*)|\033[36;01m❯❯❯❯\033[0m");
		if (!s || !check_in(s))
			continue ;
		fill_cmds(s, env);
		iterate_cmds(g_v);
		// while (g_v)
		// {
		// 	for (int i = 0; g_v->cmdsp[i]; i++)
		// 		printf(">%s<\n", g_v->cmdsp[i]);
		// 	g_v = g_v->next;
		// }
		//system("leaks minishell");
		//m = expend(env, s, 0);
		// print(0, 33, s);
		// free(s);
	}
}
