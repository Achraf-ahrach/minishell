/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:46 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/08 21:03:12 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
# include <fcntl.h>
#include <unistd.h>
#include "./libft/libft.h"

typedef struct t_env
{
	char *key;
	char *value;
	struct t_env *next;
} t_env ;

typedef struct s_list
{
	char			**cmd;
	//char			*cmd;
	char			**envir;
	int				infile;
	int				outfile;
	char			*limiter;
	//int				is_d;
	//int				stat;
	t_env			*env;
	const char		*err; // 2
	struct s_list	*next;
}					t_list;

enum TOKEN
{
	HEREDOC,
	INFILE,
	OUTFILE,
	COMMAND,
	ARG,
} ;

#endif