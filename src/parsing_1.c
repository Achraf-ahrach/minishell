/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
/*   Updated: 2023/03/14 13:08:39 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmds(char *s, t_env *env)
{
	char	**c;
	int		i;

	c = ft_split(add_spc(s, 0, 0, '<'), '|');
	i = 0;
	while (c && c[i])
		ft_lstadd_back(&g_v, ft_lstnew(c[i++], env));
	if (c[i])
		free(c[i]);
}

// void	util_expend(char *s, int *i, char c)
// {

// }

int	main(int ac, char **av, char **ev)
{
	char	*s;
	char	*m;
	t_env	*env;
	t_env	*j;

	(void)ac;
	(void)av;
	g_v = 0;
	env = 0;
	env = getlstenv(ev);
	j = env;
	while (1)
	{
		s = readline("\033[0;32mMINISHELL#(*_*)|\033[36;01m❯❯❯❯\033[0m");
		if (!s)
			continue ;
		m = expend(env, s, 0);
		print(0, 33, m);
		free(s);
		free(m);
	}
}
