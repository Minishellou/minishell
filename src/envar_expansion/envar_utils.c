/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:02:42 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/15 17:11:56 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_env_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z' ))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '?' || c == '_')
		return (1);
	return (0);
}

int	has_envar(char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '$')
		i++;
	return (string[i]);
}
