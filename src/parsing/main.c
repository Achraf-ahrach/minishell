/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:27:58 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/06 15:27:30 by aahrach          ###   ########.fr       */
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
	if (c)
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

void	add_oldped_pwd(t_env **env)
{
	char	buffer[PATH_MAX];
	t_env	*new;
	
	getcwd(buffer, sizeof(buffer));
	*env = env_new(ft_strdup("PWD"), ft_strdup(buffer));
	new = env_new(ft_strdup("SHLVL"), ft_strdup("1"));
	(*env)->next = new;
	new = env_new(ft_strdup("OLDPWD"), NULL);
	(*env)->next->next = new;
}

int	main(int ac, char **av, char **ev)
{
	char	*s;
	t_env	*env;
	t_var	*var;

	(void)ac;
	init_variables(&env, &var, av, ev);
	if (!env)
		add_oldped_pwd(&env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
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
		printf_list(g_v);
		execution();
		env = g_v->env;
		lstfree(g_v, env, var);
	}
}
