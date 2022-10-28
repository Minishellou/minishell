/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:31:47 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 12:52:18 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_garbage* new_lst(void *addr)
{
    t_garbage* node = malloc(sizeof(t_garbage));

    if (!node)
        return NULL;
    node->addr = addr;
    node->next = NULL;
    return (node);
}

t_garbage* ft_lstlast(t_garbage *genisis_block)
{
    while (genisis_block->next)
    {
        genisis_block = genisis_block->next;
    }
    return (genisis_block);
}

void    lst_addback(t_garbage **alst, t_garbage *new)
{
    if (!new)
        return ;
    else if (*alst)
        ft_lstlast(*alst)->next = new;
    else
        *alst = new;
}
