/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/03/16 16:57:34 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

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

void	oneby_one(char *s, char ***cmd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		add_arg(s, &i, cmd->cmd);
		openfile()
	}
}
void	iterate_cmds(t_list *lst)
{
	char **cmd;
	int i;

	i = 0;

	while (lst)
	{
		cmd = NULL;
		oneby_one(lst, &cmd);
		lst->cmdsp = cmd;
		lst = lst->next;
	}
}