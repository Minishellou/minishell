/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:02:42 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/09 14:26:19 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_envar(char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '$')
		i++;
	return (string[i]);
}
