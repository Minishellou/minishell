/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:47:45 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 15:58:48 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	empty_char(const char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
			return (1);
		str++;
	}
	return (0);
}

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

int	array_to_rehestablish(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i][0] == ' ' && ft_strlen((*str)[i]) <= 2)
			return (ERROR);
		quote_neon(&(*str)[i++]);
	}
	return (SUCCESS);
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
