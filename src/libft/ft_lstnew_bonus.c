/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:55:51 by ajari             #+#    #+#             */
/*   Updated: 2023/04/01 17:30:20 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	util(t_list *p, char **cmd, t_env *ev, t_var *var)
{
	p->cmd = cmd;
	p->i_f = -2;
	p->o_f = -2;
	p->stat = 1;
	p->env = ev;
	p->cmdsp = NULL;
	p->next = NULL;
	p->var = var;
	if (p->env)
		p->env->equals = 1;
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
