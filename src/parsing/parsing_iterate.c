/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/03/17 08:47:11 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	add_arg(char *s, int *i, char ***cmd)
{
	char	*str;

	str = NULL;
	while (ft_isspace(s[*i]))
		*i += 1;
	if (s[*i] != '<' && s[*i] != '>')
	{
		while (!ft_isspace(s[*i]) && s[*i])
		{
			add_char(&str, s[*i]);
			*i += 1;
		}
		add_str(cmd, str);
	}
}

void	iterate_cmds(t_list *lst)
{
	int i;

	i = 0;

	while (lst)
	{
		// for (int i = 0; lst->cmd[i]; i++)
		// 	printf("%d%s\n", i, lst->cmd[i]);
		lst = lst->next;
	}
}