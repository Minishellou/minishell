/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:20:48 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/07 10:14:34 by mcorso           ###   ########.fr       */
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

t_node	*create_redirection(char *file_path)
{
	t_redirection	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->file_path = file_path;
	new_node->next = NULL;
	return ((t_node *)new_node);
}
