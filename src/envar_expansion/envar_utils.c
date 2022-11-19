/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:02:42 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/19 12:02:54 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fill_env_node(char *var, t_env_node *node)
{
	int		i;
	char	*var_cpy;

	i = 0;
	var_cpy = ft_strdup(var);
	if (!var_cpy)
		return (ERROR);
	while (var[i] != '=')
		i++;
	var[i] = '\0';
	node->name = var;
	node->value = &var[i + 1];
	return (SUCCESS);
}