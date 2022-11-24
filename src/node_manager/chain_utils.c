/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:29:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/24 15:42:15 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*make_chain_from_array(char **array, t_node_creator create_node)
{
	int		i;
	t_node	**new_node;
	t_node	*first_node;

	i = 0;
	first_node = create_node(array[i++]);
	if (first_node == NULL)
		return (NULL);
	new_node = &first_node->next;
	while (array[i] != NULL)
	{
		*new_node = create_node(array[i++]);
		if (*new_node == NULL)
			return (NULL);
		new_node = &(*new_node)->next;
	}
	return (first_node);
}
