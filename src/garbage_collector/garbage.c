/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:31:47 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 21:07:55 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_garbage_node	*new_node(void *addr)
{
	t_garbage_node	*new_node;

	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (NULL);
	new_node->addr = addr;
	new_node->next = NULL;
	return (new_node);
}

t_garbage_node	*ft_lstlast(t_garbage_node *genisis_block)
{
	while (genisis_block->next)
	{
		genisis_block = genisis_block->next;
	}
	return (genisis_block);
}

void	lst_addback(t_garbage_node **alst, t_garbage_node *new_node)
{
	if (!new_node)
		return ;
	else if (*alst)
		ft_lstlast(*alst)->next = new_node;
	else
		*alst = new_node;
}
