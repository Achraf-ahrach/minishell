/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:04:48 by ajari             #+#    #+#             */
/*   Updated: 2023/03/16 12:01:45 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*t;

	if (new &&lst)
	{
		if (*lst)
		{
			t = *lst;
			while (t->next != NULL)
				t = t->next;
			t->next = new;
		}
		else
			*lst = new;
	}
}
