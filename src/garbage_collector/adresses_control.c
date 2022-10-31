/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adresses_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:33:33 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/31 11:00:08 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_malloc(int len, t_global **global)
{
	void	*new_block;

	new_block = malloc(len);
	lst_addback(global, new_lst(new_block));
	return (new_block);
}

void	ft_free(t_global **global)
{
	t_garbage_node	*tmp;

	while ((*global)->garbage_collector)
	{
		free((*global)->garbage_collector->addr);
		(*global)->garbage_collector->addr = NULL;
		tmp = (*global)->garbage_collector;
		(*global)->garbage_collector = (*global)->garbage_collector->next;
		free(tmp);
	}
}
