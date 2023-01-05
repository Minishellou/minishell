/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:20:48 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/05 14:58:11 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_lexer_node(char *word)
{
	t_lexer_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->word = word;
	new_node->next = NULL;
	return ((t_node *)new_node);
}

t_node	*create_env_node(char *var)
{
	t_env_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	if (fill_env_node(var, new_node) == ERROR)
		return (NULL);
	new_node->next = NULL;
	return ((t_node *)new_node);
}

t_node	*create_redirection(char *argument)
{
	t_redirection	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->argument = argument;
	new_node->next = NULL;
	return ((t_node *)new_node);
}
