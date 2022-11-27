/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:29:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/21 09:42:44 by mcorso           ###   ########.fr       */
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

void	include_subchain_at(t_node **this_node, t_node *subchain)
{
	t_node	*next_to_this_node;
	t_node	*last_subchain_node;
	
	next_to_this_node = (*this_node)->next;
	*this_node = subchain;
	last_subchain_node = last_node(subchain);
	last_subchain_node->next = next_to_this_node;
}

t_node	*last_node(t_node *current_node)
{
	if (current_node->next == NULL)
		return (current_node);
	return(last_node(current_node->next));
}
