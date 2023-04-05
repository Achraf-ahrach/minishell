/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:04:48 by ajari             #+#    #+#             */
/*   Updated: 2023/04/05 12:44:05 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*t;

	if (new && lst)
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
