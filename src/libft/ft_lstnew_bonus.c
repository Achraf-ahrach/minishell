/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:55:51 by ajari             #+#    #+#             */
/*   Updated: 2023/03/24 14:38:46 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	util(t_list *p, char **cmd, t_env *ev, t_var *var)
{
	p->cmd = cmd;
	p->h_d = NULL;
	p->infile = -1;
	p->outfile = -1;
	p->stat = 0;
	p->env = ev;
	p->cmdsp = NULL;
	p->err = NULL;
	p->next = NULL;
	p->var = var;
}

t_list	*ft_lstnew(char **cmd, t_env *ev, t_var *var)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (!p)
		return (NULL);
	util(p, cmd, ev, var);
	return (p);
}
