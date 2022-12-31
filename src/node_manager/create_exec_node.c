/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:38:32 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/26 11:55:08 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node *create_exec_node(char *word)
{
	t_exec_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	if (word)
		new_node->command_path = ft_strdup(word);
	new_node->next = NULL;
	return ((t_node *)new_node);
}