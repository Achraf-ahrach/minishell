/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
/*   Updated: 2023/03/07 18:01:59 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chck_pipe(char *s)
{
	char	c;

	if (s[0] == '|' || s[ft_strlen(s) - 1] == '|' || s[ft_strlen(s) - 1] == '>'
		|| s[ft_strlen(s) - 1] == '<')
	{
		(s[0] == '|') && (c = '|');
		(s[ft_strlen(s) - 1] == '|') && (c = '|');
		(s[ft_strlen(s) - 1] == '<') && (c = '<');
		(s[ft_strlen(s) - 1] == '>') && (c = '>');
		exit(error(c, "syntax error near unexpected token"));
	}
	return (1);
}

static void	rm_quote_uti(char *s, int *i)
{
	if (s[*i] == '|')
		s[*i] = 2;
	else if (s[*i] == '>')
		s[*i] = 3;
	else if (s[*i] == '<')
		s[*i] = 4;
	i += 1;
}

void	rm_quote(char *s, int i, char c)
{
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			s[i] = 1;
			while (s[i] != c && s[i])
				rm_quote_uti(s, &i);
			if (!s[i])
				exit(error(c, "don't forget to close quote after opening it"));
			s[i] = 1;
		}
		i++;
	}
}

int	ft_strlen_spc(char *s, char c)
{
	int	j;
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (chck_pipe(s) && s[i])
	{
		j = 0;
		(s[i] == c) && (count += 2);
		while (s[i] == c)
		{
			i++;
			j++;
			count++;
		}
		if (j > 2)
			print('\0', 31, "Error in < or > ");
		if (!s[i])
			break ;
		count++;
		i++;
	}
	return (count);
}

static void	util_addspc(char *s, char *dup, int *i, int *j)
{
	char	c;

	c = s[*i];
	dup[*i + *j] = ' ';
	*j += 1;
	while (s[*i] == c)
	{
		dup[*i + *j] = s[*i];
		*i += 1;
	}
	dup[*i + *j] = ' ';
	*j += 1;
}

char	*add_spc(char *s, int i, int j, char c)
{
	char	*dup;

	dup = malloc(sizeof(char) * ft_strlen_spc(s, c) + 1);
	if (!dup)
		return (dup);
	while (s[i])
	{
		if (s[i] == c)
			util_addspc(s, dup, &i, &j);
		else
		{
			dup[i + j] = s[i];
			i++;
		}
	}
	dup[i + j] = 0;
	free(s);
	if (c == '<')
		dup = add_spc(dup, 0, 0, '>');
	return (dup);
}

void	fill_info(char *s, t_list **cmd)
{
	char	**c;
	int		i;

	c = ft_split(s, '|');
	i = 0;
	while (c && c[i])
	{
		ft_lstadd_back(cmd, ft_lstnew(c[i]));
		i++;
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*s;
	char	**m;
	char	*cmd;

	(void)s;
	(void)ac;
	(void)av;
	(void)ev;
	(void)cmd;
	while (1)
	{
		s = readline("\033[0;32mMINISHELL#(*_*)|\033[36;01m❯❯❯❯\033[0m");
		rm_quote(s, 0, 0);
		print('\0', 34, s);
		m = ft_split(add_spc(s, 0, 0, '<'), '|');
		for (int i = 0; m[i]; i++)
			print('\0', 33, m[i]);
	}
	system("leaks minishell");
}
