/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:29:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/10 13:46:34 by gkitoko          ###   ########.fr       */
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

void	lex_addback(t_lexer_node **node, t_lexer_node *new)
{
	t_lexer_node	*last;
	
	if (!node)
		return ;
	else if (*node)
	{
		last = (t_lexer_node *)last_node((t_node *)*node);
		last->next = new;
	}
	else
	{
		*node = new;
	}
}

void unit_free(void *node)
{
	t_garbage_node	*tmp;

	tmp = NULL;
	while (g_glo.garbage_ctr)
	{
		if (g_glo.garbage_ctr->addr == node)
		{
			printf("\ngarbage addr-> %p\n", g_glo.garbage_ctr->addr);
			printf("\nnode-> %p\n", node);
			free(g_glo.garbage_ctr->addr);
			g_glo.garbage_ctr->addr = NULL;
			tmp = g_glo.garbage_ctr;
			g_glo.garbage_ctr = g_glo.garbage_ctr->next;
			free(tmp);
		}
		else
			g_glo.garbage_ctr = g_glo.garbage_ctr->next;
	}
}

void remove_node(t_node **current_node)
{
	t_node *node;
	if (!*current_node)
		return ;
	node = *current_node;
	*current_node = (*current_node)->next;
	unit_free(node);
}
