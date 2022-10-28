/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adresses_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:33:33 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 21:05:27 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_malloc(int len, t_garbage_node **genisis_block)
{
	void	*new_block;

	new_block = malloc(len);
	lst_addback(genisis_block, new_lst(new_block));
	return (new_block);
}

void	ft_free(t_garbage_node	*genisis_block)
{
	t_garbage_node	*tmp;

	while (genisis_block)
	{
		tmp = genisis_block;
		free(genisis_block->addr);
		genisis_block->addr = NULL;
		genisis_block = genisis_block->next;
		free(tmp);
	}
}
