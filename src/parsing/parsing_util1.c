/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:08:41 by ajari             #+#    #+#             */
/*   Updated: 2023/03/28 18:06:11 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	free_one(t_list *list)
{
	int	i;

	i = 0;
	while (list->cmd && list->cmd[i])
		free(list->cmd[i++]);
	if (list->cmdsp)
		free(list->cmdsp);
	if (list->cmd)
		free(list->cmd);
	free(list);
}

void	lstfree(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free_one(list);
		list = tmp;
	}
}

void	addmany_chars(char **dup, char *s, int fre)
{
	int	i;

	i = 0;
	while (s[i])
	{
		add_char(dup, s[i]);
		i++;
	}
	if (fre)
		free(s);
}
