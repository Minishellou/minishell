/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:02:42 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/09 12:54:35 by gkitoko          ###   ########.fr       */
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
