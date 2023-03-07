/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:38:37 by ajari             #+#    #+#             */
/*   Updated: 2023/03/05 18:55:01 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(char c, int color, char *str)
{
	(void)c;
	if (color == 31)
		printf(RED);
	else if (color == 32)
		printf(GREEN);
	else if (color == 33)
		printf(WELLOW);
	else if (color == 34)
		printf(BLUE);
	else
		printf(AS_DEFAULT);
	printf("%s\n", str);
}
