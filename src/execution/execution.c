/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/16 10:33:12 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	builtins()
{
	if (!ft_strcmp(data->cmdsp[0], "echo"))
		echo(data->cmdsp);
	else if (!ft_strcmp(data->cmdsp[0], "pwd"))
		pwd(0);
	else if (!ft_strcmp(data->cmdsp[0], "cd"))
		cd();
	else if (!ft_strcmp(data->cmdsp[0], "export"))
		export();
	else if (!ft_strcmp(data->cmdsp[0], "unset"))
		unset(data);
	else if (!ft_strcmp(data->cmdsp[0], "env"))
		env(data->env);
	else if (!ft_strcmp(data->cmdsp[0], "exit"))
		exit(0);
}

void	execution()
{
	t_list *list;
	int		i;

	i = 0;
	data->env = getlstenv(data->envir);
	list = data;
	while (list)
	{
		if (list->infile)
			dup2(0, list->infile);
		if (list->outfile)
			dup2(1, list->outfile);
		builtins();
		
	}
}

int main(int main, char **av, char **env)
{
	data = malloc(sizeof(t_list));
	data->envir = env;
	data->cmdsp = malloc(4 * sizeof(char *));
	data->cmdsp[0] = av[1];
	data->cmdsp[1] = av[2];
	data->cmdsp[2] = av[3];
	data->cmdsp[3] = NULL;
	execution();
}