/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:10:31 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/09 14:26:13 by gkitoko          ###   ########.fr       */
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
