/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:29:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/20 15:42:46 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*make_chain_from_array(char **array, t_node_creator create_node)
{
	int		i;
	t_node	**new_node;
	t_node	*first_node;

	i = 0;
	first_node = NULL;
	if (array[0])
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
	if (!current_node)
		return (NULL);
	while (current_node->next)
		current_node = current_node->next;
	return (current_node);
}

void	lex_addback(t_lexer_node **node, t_lexer_node *new_node)
{
	t_lexer_node	*last;

	if (!node)
		return ;
	if (*node)
		last = (t_lexer_node *)last_node((t_node *)*node);
	else
		last = *node;
	last->next = new_node;
}
