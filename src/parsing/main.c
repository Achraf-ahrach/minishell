/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:27:58 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/10 15:58:58 by ajari            ###   ########.fr       */
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

void	shlvl(t_env **env)
{
	t_env	*tmp;
	int		nb;
	char	*nbr;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			if (tmp->value)
			{
				nb = ft_atoi(tmp->value);
				nb += 1;
				free(tmp->value);
				nbr = ft_itoa(nb);
				tmp->value = ft_strdup(nbr);
				free(nbr);
			}
			else
				tmp->value = ft_strdup("1");
		}
		tmp = tmp->next;
	}
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
	else
		shlvl(&env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint);
		s = readline("MINISHELL#(*_*)|❯❯❯❯ ");
		if (!s)
			exit(var->exit_status);
		add_history(s);
		if (!check_in(s) && freee(s))
			continue ;
		fill_cmds(s, env, var);
		execution();
		lstfree(g_v, env, var);
	}
}
