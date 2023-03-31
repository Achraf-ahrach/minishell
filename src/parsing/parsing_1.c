/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/31 16:17:23 by ajari            ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2023/03/30 15:19:20 by aahrach          ###   ########.fr       */
=======
/*   Updated: 2023/03/31 14:30:58 by ajari            ###   ########.fr       */
>>>>>>> 8d8922e07eb654a2bcd4c280aef5afe205f7fb36
>>>>>>> 0cf2684734520e7a5ce65227e80ac1a7b033db8c
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	fill_cmds(char *s, t_env *env, t_var *var)
{
	char	**c;
	int		i;

	i = 0;
	g_v = ft_lstnew(0, env, var);
	c = ft_split(expend(add_spc(s, 0), 0, 1), '|', 1);
	free(g_v);
	g_v = 0;
	while (c && c[i])
		ft_lstadd_back(&g_v, ft_lstnew(ft_split(c[i++], ' ', 1), env, var));
	free(c);
	iterate_cmds(g_v, 0);
}

void	printf_list(t_list *tem)
{
	char	ss[1000];

	while (tem)
	{
		printf("<<<<<<<<<<<<<<<<pipe>>>>>>>>>>>>>>>>>>>>>\n");
		for (int i = 0; tem->cmdsp && tem->cmdsp[i]; i++)
		{
			if (!i)
				printf("cmd:");
			printf("#%s# ", tem->cmdsp[i]);
		}
		printf("\nstat:%d\ninfile:%d\n", tem->stat, tem->i_f);
		if (0 && tem->i_f != -1 && tem->i_f != -2)
		{
			read(tem->i_f, ss, 100);
			printf("%s\n", ss);
		}
		printf("outfile:%d\n", tem->o_f);
		tem = tem->next;
	}
}

void	crl_c(int k)
{
	(void)k;
	printf("exit hello\n");
	exit(0);
}

void	init_variables(t_env **ev, t_var **var, char **av, char **env)
{
	(void)av;
	*ev = getlstenv(env);
	*var = malloc(sizeof(t_var));
	if (!*var)
		exit(error("Error of allocation", "struct var"));
	(*var)->exit_status = 0;
}

int	main(int ac, char **av, char **ev)
{
	char	*s;
	t_env	*env;
	t_var	*var;

	(void)ac;
	init_variables(&env, &var, av, ev);
	while (1)
	{
		//signal(SIGINT, &crl_c);
		s = readline("MINISHELL#(*_*)|❯❯❯❯");
		add_history(ft_strdup(s)); //choufni a moul lparsing
		if (!s || !check_in(s))
			continue ;
		fill_cmds(s, env, var);
		printf_list(g_v);
		execution();
		lstfree(g_v);
		//system("leaks minishell");
	}
}
