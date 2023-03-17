/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/16 20:32:54 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	builtins()
{
	if (!ft_strcmp(g_v->cmdsp[0], "echo"))
		echo(g_v->cmdsp);
	else if (!ft_strcmp(g_v->cmdsp[0], "pwd"))
		pwd(0);
	else if (!ft_strcmp(g_v->cmdsp[0], "cd"))
		cd();
	else if (!ft_strcmp(g_v->cmdsp[0], "export"))
		export();
	else if (!ft_strcmp(g_v->cmdsp[0], "unset"))
		unset(g_v);
	else if (!ft_strcmp(g_v->cmdsp[0], "env"))
		env(g_v->env);
	else if (!ft_strcmp(g_v->cmdsp[0], "exit"))
		ft_exit();
}

void	execution(char **env)
{
	t_list *list;
	int		i;

	i = 0;
	g_v->env = getlstenv(env);
	list = g_v;
	if (ft_lstsize(list) == 1)
		builtins();
	while (list)
	{
		if (list->infile)
			dup2(0, list->infile);
		if (list->outfile)
			dup2(1, list->outfile);
		//builtins();
	}
}

int main(int main, char **av, char **env)
{
	g_v = malloc(sizeof(t_list *));
	g_v->cmdsp = malloc(4 * sizeof(char *));
	g_v->cmdsp[0] = av[1];
	g_v->cmdsp[1] = av[2];
	g_v->cmdsp[2] = av[3];
	g_v->cmdsp[3] = NULL;
	execution(env);
}