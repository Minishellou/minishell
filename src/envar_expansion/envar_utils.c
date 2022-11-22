/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:02:42 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/22 12:16:29 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fill_env_node(char *var, t_env_node *node)
{
	int		i;

	i = 0;
	while (var[i] != '=')
		i++;
	var[i] = '\0';
	node->name = var;
	node->value = &var[i + 1];
	return (SUCCESS);
}