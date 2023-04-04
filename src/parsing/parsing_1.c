/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/04 15:01:20 by aahrach          ###   ########.fr       */
=======
/*   Updated: 2023/04/03 13:49:28 by ajari            ###   ########.fr       */
>>>>>>> eaf0c4ec2dea294d004c773e84bf7fb2722259a2
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
	c = ft_split(expend(add_spc(s, 0), 0, 1, &i), '|', 1);
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

void	sig_handler_crl_c(int sig)
{
	(void)sig;
	// g_v->var->exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler_crl_(int sig)
{
	(void)sig;
	exit_status(131, 1);
}

void	sig_handler_crl(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit_status(1, 1);
}

void	sig_handler_crl__(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
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
		signal(SIGINT, sig_handler_crl_c);
		s = readline("MINISHELL#(*_*)|❯❯❯❯ ");
		if (!s)
			exit(var->exit_status);
		add_history(s);
		if (!check_in(s))
			continue;
		fill_cmds(s, env, var);
		//printf_list(g_v);
		execution(&env);
		env = g_v->env;
		lstfree(g_v);
		//free(s);
		//system("leaks minishell");
	}
}
