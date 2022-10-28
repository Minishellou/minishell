/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adresses_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:33:33 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 16:30:40 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void* ft_malloc(int len, t_garbage_node** genisis_block)
{
    void* new_m = malloc(len);

    lst_addback(genisis_block, new_lst(new_m));
    return (new_m);
}

void ft_free(t_garbage_node* genisis_block)
{
    t_garbage_node *tmp;

    while (genisis_block)
    {
        free(genisis_block->addr);
		genisis_block->addr = NULL;
        tmp = genisis_block;
        genisis_block = genisis_block->next;
        free(tmp);
		tmp = NULL;
    }
}