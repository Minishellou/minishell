/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:20:48 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/01 17:34:50 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_lexer_node(char *word)
{
	t_lexer_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	new_node->word = word;
	new_node->next = NULL;
	return ((t_node *)new_node);
}

t_node	*create_env_node(char *var)
{
	t_env_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	new_node->var = var;
	new_node->next = NULL;
	return ((t_node *)new_node);
}
