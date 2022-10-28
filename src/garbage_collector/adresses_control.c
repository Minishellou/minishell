/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adresses_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:33:33 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 12:39:05 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void* ft_malloc(int len, t_garbage** genisis_block)
{
    void* new_m = malloc(len);

    lst_addback(genisis_block, new_lst(new_m));
    return (new_m);
}

void ft_free(t_garbage* genisis_block)
{
    t_garbage *tmp;

    while (genisis_block)
    {
        free(genisis_block->addr);
        tmp = genisis_block;
        genisis_block = genisis_block->next;
        free(tmp);
    }
}