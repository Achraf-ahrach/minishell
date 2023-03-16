/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:24:47 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/04 18:27:09 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>

int		ft_memcmp(char *s1, char *s2);
char	*ft_check(char **p, char *comand);
char	*ft_join(char *p);
char	*ft_strjoin(char *s1, char *s2);
void	ft_free(char **p);
int		ft_strlen(char *s);
int		ft_strnstr(char **haystack, char *needle, int len);
char	**ft_split(char *s, char c);
char	*get_next_line(int fd);
void	her_doc(char **av, char **env);
void	ft_child1_BUN(char **av, char **env, int *pi, int i);
int		fd_open_wr(char **av);
#endif