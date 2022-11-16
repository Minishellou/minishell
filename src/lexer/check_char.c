/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:26:31 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/15 16:28:29 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    is_white_space(char c)
{
    if (c == ' ' || c == '\t'|| c == '\r')
        return (1);
    return (0);
}

int ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}