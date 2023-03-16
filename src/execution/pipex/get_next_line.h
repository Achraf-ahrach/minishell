/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:06:57 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/04 18:24:40 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*ft_free_get(char *buf, char **p);
char	*get_next_line(int fd);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_strdup_get(char *s1);
int		check_line_get(char *str);
char	*ft_substr_get(char *str, int start, int len, int x);
size_t	ft_strlen_get(char *s);
#endif
