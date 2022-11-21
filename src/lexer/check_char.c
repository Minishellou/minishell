/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:26:31 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/21 11:05:56 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
 
int   is_white_space(char c)
{
    if (c == ' ' || c == '\t'|| c == '\r')
        return (1);
    return (0);
}

int is_special_token(char c)
{
	if (c == PIPE)
	    return (1);
    if (c == LESS)
        return (1);
    if (c == GREAT)
        return (1);
    return (0);
}