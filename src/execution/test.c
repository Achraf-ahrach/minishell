#include "../minishell.h"

int	ft_lstsize_env(t_env *env)
{
	int size;

	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

void	export_add(t_list *list, char *key, char *str)
{
	char	**e;

	if (!ft_strcmp(str, "present"))
	{
		while (list->env)
		{
			if (!ft_strcmp(list->env->key, key))
			{
				list->env->value = key;
				return ;
			}
			list->env = list->env->next;
		}
	}
	else if (!ft_strcmp(str, "present"))
	{
		e = ft_split(str, '=');
		envadd_back(&list->env, env_new(e[0], e[1]));
	}
}

char	*come_max(t_env *env)
{
	char	*max;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->index == 0)
			max = tmp->key;
		tmp = tmp->next;
	}
	while (env)
	{
		if (ft_strcmp(max, env->key) < 0)
		{
			if (env->index == 0)
				max = env->key;
		}
		env = env->next;
	}
	return (max);
}


void	sort_export(t_env *env)
{
	int		size;
	char	*max;
	t_env	*tmp;
	int		j;

	j = 1;
	size = ft_lstsize_env(env);
	while (j <= size)
	{
		tmp = env;
		max = come_max(env);
		while (1)
		{
			if (ft_strcmp(max, tmp->key) == 0)
			{
				tmp->index = j;
				j++;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	export(t_list *list)
{
	int		i;
	int		j;
	int 	size;
	t_env	*tmp;

	i = 1;
	if (!list->cmdsp[i])
	{
		sort_export(list->env);
		size = ft_lstsize_env(list->env);
		while (size > 0)
		{
			tmp = list->env;
			while (tmp)
			{
				if (tmp->index == size)
				{
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
					size--;
					break ;
				}
				tmp = tmp->next;
			}
		}
	}
	else
	{
		tmp = list->env;
		while (list->cmdsp[i])
		{
			j = 0;
			while (tmp)
			{
				if (!ft_strcmp(tmp->key, list->cmdsp[i]))
				{
					export_add(list, list->cmdsp[i], "present");
					j = 1;
				}
				tmp = tmp->next;
			}
			if (j == 0)
				export_add(list, list->cmdsp[i], "absent");
			i++;
		}
	}
}


void	builtins(t_list *list)
{
	// if (!ft_strcmp(list->cmd[0], "echo"))
	// 	echo(list->cmd);
	// else if (!ft_strcmp(list->cmd[0], "pwd"))
	// 	pwd(0);
	// else if (!ft_strcmp(list->cmd[0], "cd"))
	// 	cd(list->cmd);
	if (!ft_strcmp(list->cmdsp[0], "export"))
		export(list);
}

static void	execution(t_list *list)
{
	int	i;

	i = 0;
	list->env = getlstenv(list->envir);
	// while (list)
	// {
		builtins(list);
	// }
}

// int main(int ac, char **av, char **env)
// {
// 	t_list	*list;

// 	list = malloc(sizeof(t_list));
// 	list->envir = env;
// 	list->cmdsp =  malloc(sizeof(char *) * 3);
// 	list->cmdsp[0] = av[1];
// 	list->cmdsp[1] = av[2];
// 	list->cmdsp[2] = NULL;
// 	execution(list);
// }