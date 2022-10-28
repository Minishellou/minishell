/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:31:47 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 16:26:56 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_garbage_node* new_lst(void *addr)
{
    t_garbage_node* node = malloc(sizeof(t_garbage_node));

    if (!node)
        return NULL;
    node->addr = addr;
    node->next = NULL;
    return (node);
}

t_garbage_node* ft_lstlast(t_garbage_node *genisis_block)
{
    while (genisis_block->next)
    {
        genisis_block = genisis_block->next;
    }
    return (genisis_block);
}

void    lst_addback(t_garbage_node **alst, t_garbage_node *new)
{
    if (!new)
        return ;
    else if (*alst)
        ft_lstlast(*alst)->next = new;
    else
        *alst = new;
}
