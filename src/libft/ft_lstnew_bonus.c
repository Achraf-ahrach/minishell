/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:55:51 by ajari             #+#    #+#             */
/*   Updated: 2023/03/15 19:10:07 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	utillst(t_list *new, char *cmd, t_env *ev)
{
	new->cmd = cmd;
	new->limiter = NULL;
	new->infile = -2;
	new->outfile = -2;
	new->stat = 0;
	new->env = ev;
	new->err = NULL;
	new->next = NULL;
}

t_list	*ft_lstnew(char *cmd, t_env *ev)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (!p)
		return (NULL);
	utillst(p, cmd, ev);
	return (p);
}
