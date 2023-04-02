/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:08:41 by ajari             #+#    #+#             */
/*   Updated: 2023/04/02 19:41:04 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	free_one(t_list *list, int i)
{
	while (list->cmd && list->cmd[i])
		free(list->cmd[i++]);
	if (list->cmdsp)
		free(list->cmdsp);
	if (list->cmd)
		free(list->cmd);
	if (list->i_f >= 0)
		close(list->i_f);
	if (list->o_f >= 0)
		close(list->o_f);
	free(list);
}

void	lstfree(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free_one(list, 0);
		list = tmp;
	}
}

void	add_char(char **s, char c)
{
	char	*add;
	int		len;

	len = ft_strlen(*s);
	add = malloc(len + 2);
	if (!add)
		exit(error("error allocation", *s));
	if (*s)
	{
		ft_strcpy(add, *s);
		free(*s);
	}
	add[len] = c;
	add[len + 1] = 0;
	*s = add;
}

int	add_chars(char **dup, char *s, int fre)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		add_char(dup, s[i]);
		i++;
	}
	if (fre)
		free(s);
	return (1);
}

void	add_str(char ***s, char *str)
{
	int		i;
	char	**m;

	i = 0;
	while (*s && (*s)[i])
		i++;
	m = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (*s && (*s)[i])
	{
		m[i] = (*s)[i];
		i++;
	}
	m[i++] = str;
	m[i] = NULL;
	if (*s)
		free(*s);
	*s = m;
}
