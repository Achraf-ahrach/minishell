/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
/*   Updated: 2023/03/24 14:39:01 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	fill_cmds(char *s, t_env *env)
{
	t_var	*var;
	char	**c;
	int		i;

	c = ft_split(add_spc(s, 0), '|', 1);
	i = 0;
	var = malloc(sizeof(t_var));
	if (!var)
		exit(error(0, "allocation error"));
	while (c && c[i])
		ft_lstadd_back(&g_v, ft_lstnew(ft_split(c[i++], ' ', 1), env, var));
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
		tem = g_v;
		while (g_v)
		{
			printf("<<<<<<<<<<<<<<<<pipe>>>>>>>>>>>>>>>>>>>>>\n");
			for (int i = 0; g_v->cmdsp && g_v->cmdsp[i]; i++)
			{
				if (!i)
					printf("cmd:");
				printf("%s ", g_v->cmdsp[i]);
			}
			printf("\nstat:%d\ninfile:%d\n", g_v->stat, g_v->infile);
			printf("outfile:%d\nh_doc:%s\n", g_v->outfile, g_v->h_d);
			g_v = g_v->next;
		}
		//lstfree(tem);
		system("leaks minishell");
	}
}
