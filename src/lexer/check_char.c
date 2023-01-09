/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:26:31 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 16:00:03 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
