/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:31:47 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/01 11:02:23 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static
t_garbage_node	*new_grb_node(void *addr)
{
	t_garbage_node	*new_node;

	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (NULL);
	new_node->addr = addr;
	new_node->next = NULL;
	return (new_node);
}

static
t_garbage_node	*ft_lstlast(t_garbage_node *genisis_block)
{
	while (genisis_block->next)
	{
		genisis_block = genisis_block->next;
	}
	return (genisis_block);
}

static
void	lst_addback(t_garbage_node *new_node)
{
	if (!new_node)
		return ;
	else if (global.garbage_ctr)
		ft_lstlast((*global)->garbage_ctr)->next = new_node;
	else
		(global.garbage_ctr = new_node;
}

void	*ft_malloc(int len)
{
	void	*new_block;

	new_block = malloc(len);
	lst_addback(new_grb_node(new_block));
	return (new_block);
}

void	ft_free(void)
{
	t_garbage_node	*tmp;

	while (global.garbage_c
t_garbage_node	*ft_lst