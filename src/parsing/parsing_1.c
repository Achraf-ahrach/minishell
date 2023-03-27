/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
/*   Updated: 2023/03/27 16:00:05 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	fill_cmds(char *s, t_env *env, t_var *var)
{
	char	**c;
	int		i;

	i = 0;
	c = ft_split(add_spc(s, 0), '|', 1);
	while (c && c[i])
		ft_lstadd_back(&g_v, ft_lstnew(ft_split(c[i++], ' ', 1), env, var));
	free(c);
}

int	main(int ac, char **av, char **ev)
{
	char	*s;
	char	ss[1000];
	int		i;
	char	**m;
	t_env	*env;
	t_env	*j;
	t_list	*tem;
	t_var	*var;

	(void)ac;
	(void)av;
	(void)i;
	(void)tem;
	(void)ss;
	env = 0;
	env = getlstenv(ev);
	var = malloc(sizeof(t_var));
	if (!var)
		return (error(0, "error en allocation"));
	j = env;
	m = NULL;
	i = 0;
	while (1)
	{
		g_v = 0;
		s = readline("\033[0;32mMINISHELL#(*_*)|\033[36;01m❯❯❯❯\033[0m");
		//add_history(ft_strdup(s)); //choufni a moul lparsing 
		if (!s || !check_in(s))
			continue ;
		fill_cmds(s, env, var);
		iterate_cmds(g_v);
		tem = g_v;
		// while (g_v)
		// {
		// 	printf("<<<<<<<<<<<<<<<<pipe>>>>>>>>>>>>>>>>>>>>>\n");
		// 	for (int i = 0; g_v->cmdsp && g_v->cmdsp[i]; i++)
		// 	{
		// 		if (!i)
		// 			printf("cmd:");
		// 		printf("%s ", g_v->cmdsp[i]);
		// 	}
		// 	printf("\nstat:%d\ninfile:%d\n", g_v->stat, g_v->i_f);
		// 	read(g_v->i_f, ss, 100);
		// 	printf("%s\n", ss);
		// 	printf("outfile:%d\n", g_v->o_f);
		// 	g_v = g_v->next;
		// }
		g_v = tem;
		execution();
		lstfree(tem);
		//system("leaks minishell");
	}
}
