/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:47:45 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/16 14:33:07 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




int white_space_to_neg(char **str)
{
    int		i;
    char	start;

    i = 1;
    start = (*str)[0];
    while ((*str)[i] && (*str)[i] != start)
	{
		if (is_white_space((*str)[i]))
			(*str)[i] *= -1;
		i++;
	}
	if ((*str)[i] != start)
		return (-1);
	return (i);
}

int	quote_space_to_neg(char **str)
{
	int 	i;
	int		return_index;
	char	*quoted_substring;

	i = 0;
	return_index = 0;
	while ((*str)[i])
	{
		if ((*str)[i] && ((*str)[i] == '"' || (*str)[i] == '\''))
		{
			quoted_substring = &(*str)[i];
			return_index = white_space_to_neg(&quoted_substring);
			if (return_index < 0)
				return (0);
			i += return_index;
		}
		i++;
	}
	return (1);
}