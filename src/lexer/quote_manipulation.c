/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:50:45 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/14 14:01:19 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	neon(char **str)
{
	int		i;
	char	start;

	i = 1;
	start = (*str)[0];
	while ((*str)[i] && (*str)[i] != start)
		(*str)[i++] *= -1;
	if ((*str)[i] != start)
		return (ERROR);
	return (i);
}

int	quote_neon(char **str)
{
	int		i;
	int		return_index;
	char	*quoted_substring;

	i = 0;
	return_index = 0;
	while ((*str)[i])
	{
		if ((*str)[i] && ((*str)[i] == '"' || (*str)[i] == '\''))
		{
			quoted_substring = &(*str)[i];
			return_index = neon(&quoted_substring);
			if (return_index < 0)
				return (ERROR);
			i += return_index;
		}
		i++;
	}
	return (SUCCESS);
}
