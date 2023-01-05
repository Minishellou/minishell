/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:46:54 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/17 22:41:23 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*get_envar(char *envar_name)
{
	size_t		envar_name_len;
	t_env_node	env;
	t_env_node	*current_node;

	env.next = g_glo.env;
	current_node = &env;
	envar_name_len = ft_strlen(envar_name) - 1;
	while (1)
	{
		current_node = current_node->next;
		if (!current_node)
			break ;
		if (ft_strncmp(current_node->name, envar_name + 1, envar_name_len))
			continue ;
		if (envar_name_len != ft_strlen(current_node->name))
			continue ;
		break ;
	}
	return (current_node);
}
