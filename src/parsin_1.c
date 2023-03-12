/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:18:42 by ajari             #+#    #+#             */
/*   Updated: 2023/03/12 13:07:02 by ajari            ###   ########.fr       */
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



static void	rm_quote_uti(char *s, int *i, char c, int this)
{
	while (this == -1 && s[*i + 1] != c && s[*i])
	{
		if (s[*i + 1] == '|')
			s[*i] = 1;
		else if (s[*i + 1] == '>')
			s[*i] = 2;
		else if (s[*i + 1] == '<')
			s[*i] = 3;
		else
			s[*i] = s[*i + 1];
		*i += 1;
	}
	while (this != -1 && s[this])
	{
		s[this] = s[this + 2];
		this ++;
	}
}
int	rm_quote(char **ev, char *s, int i, char c)
{
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			s[i] = 1;
			rm_quote_uti(s, &i, c, -1);
			if (!s[i])
			{
				free(s);
				return (error(c, "unclose quote"));
			}
			rm_quote_uti(s, &i, c, i);
		}
		else
			i++;
	}
	fill_cmds(s, ev);
	free(s);
	return (1);
}

static int	ft_strlen_spc(char *s, char c, int i, int j)
{
	int	count;

	count = 0;
	while (chck_pipe(s) && s[i])
	{
		j = 0;
		(s[i] == c && i && s[i - 1] != ' ') && (count += 1);
		while (s[i] == c)
		{
			i++;
			j++;
			count++;
		}
		if (j > 2)
			print(c, 31, "Error in ");
		(i && s[i - 1] == c && s[i] != ' ') && (count += 1);
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
	if (*i && s[*i - 1] != ' ')
	{
		dup[*i + *j] = ' ';
		*j += 1;
	}
	while (s[*i] == c)
	{
		dup[*i + *j] = s[*i];
		*i += 1;
	}
	if (s[*i] != ' ')
	{
		dup[*i + *j] = ' ';
		*j += 1;
	}
}

char	*add_spc(char *s, int i, int j, char c)
{
	char	*dup;

	dup = malloc(sizeof(char) * ft_strlen_spc(s, c, 0, 0) + 1);
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

void	fill_cmds(char *s, char **ev)
{
	char	**c;
	int		i;

	c = ft_split(add_spc(s, 0, 0, '<'), '|');
	i = 0;
	while (c && c[i])
	{
		ft_lstadd_back(&data, ft_lstnew(c[i], ev));
		free(c[i++]);
	}
	if (c)
		free(c);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	char	*s;
	t_list	*t;
	t_env	*env;
	char	*cmd;
	t_env	*j;

	(void)s;
	(void)ac;
	(void)av;
	(void)ev;
	(void)cmd;
	(void)t;
	(void)j;
	i = 0;
	data = 0;
	env = 0;
	while (1)
	{
		s = readline("\033[0;32mMINISHELL#(*_*)|\033[36;01m❯❯❯❯\033[0m");
		if (!s)
			continue ;
		rm_quote(s, 0, 0);
		printf("first one \n");
		print('\0', 34, s);
		fill_cmds(s, ev);
		t = data;
		printf("%p\n", data);
		while (t)
		{
			printf("cmd:%s\n", t->cmd);
			t = t->next;
		}
		// for (int i = 0; m[i]; i++)
		// 	print('\0', 33, m[i]);
	}
	//system("leaks minishell");
}
