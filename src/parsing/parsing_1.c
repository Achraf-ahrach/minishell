/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/04/05 12:15:20 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/05 12:16:44 by aahrach          ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Created: 2023/04/04 22:39:26 by ajari             #+#    #+#             */
/*   Updated: 2023/04/04 22:54:51 by ajari            ###   ########.fr       */
=======
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/05 12:10:28 by aahrach          ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2023/04/04 22:38:43 by ajari            ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2023/04/04 15:47:03 by aahrach          ###   ########.fr       */
=======
/*   Updated: 2023/04/04 19:46:37 by ajari            ###   ########.fr       */
>>>>>>> f40732616b53919d3a3437b05b2462ad33b51984
>>>>>>> ab8a46be672ff9c03425a985da4a5a62f410f4a5
>>>>>>> 31dac5fd3fadc1b831b9fc3d7523abd3f4104769
>>>>>>> cd0dd955ff0f427166ee57142834c19aade56cba
>>>>>>> 076f1b0a6c990f72612a8a16acafcc04114ee824
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	fill_cmds(char *s, t_env *env, t_var *var)
{
	char	**c;
	int		i;

	i = 0;
	c = ft_split(expend(add_spc(s, 0), 0, 1, &i), '|', 1);
	if (g_v)
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

void	init_variables(t_env **ev, t_var **var, char **av, char **env)
{
	(void)av;
	*ev = getlstenv(env);
	*var = malloc(sizeof(t_var));
	if (!*var)
		exit(error("Error of allocation", "struct var"));
	(*var)->exit_status = 0;
	g_v = ft_lstnew(0, *ev, *var);
}

void	sigint(int sig)
{
	(void)sig;
	printf("ja lhna 2\n");
	//dprintf(2, "hna\n");
	g_v->var->exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
	rl_redisplay();
}

void	sigquit_childe(int sig)
{
	(void)sig;
	dprintf(2, "ja \n");
	exit_status(131, 1);
}

void	sigint_herdoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit_status(1, 1);
}

void	sigint_childe(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	//rl_on_new_line();
	rl_redisplay();
	exit_status(130, 1);
}

int	main(int ac, char **av, char **ev)
{
	char	*s;
	t_env	*env;
	t_var	*var;

	(void)ac;
	signal(SIGQUIT, SIG_IGN);
	init_variables(&env, &var, av, ev);
	while (1)
	{
		signal(SIGINT, sigint);
		s = readline("MINISHELL#(*_*)|❯❯❯❯ ");
		if (!s)
		{
			printf("exit\n");
			exit(var->exit_status);
		}
		add_history(s);
		if (!check_in(s))
			continue ;
		fill_cmds(s, env, var);
		//init_variables(&env, &var, av, ev);
		//printf_list(g_v);
		execution();
		env = g_v->env;
		lstfree(g_v, env, var);
		//free(s);
		//system("leaks minishell");
	}
}
