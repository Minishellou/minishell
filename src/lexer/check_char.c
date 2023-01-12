/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:26:31 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/12 13:50:32 by gkitoko          ###   ########.fr       */
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

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (SUCCESS);
	return (ERROR);
}

int	is_special_token(char c)
{
	if (c == PIPE)
		return (SUCCESS);
	if (c == LESS)
		return (SUCCESS);
	if (c == GREAT)
		return (SUCCESS);
	return (ERROR);
}
