/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_conversion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:18:45 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/12 14:04:38 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*concat_array_to_string(char **splited_string)
{
	int		i;
	int		len;
	char	*concatened_string;

	i = 1;
	len = 0;
	if (splited_string == NULL)
		return (NULL);
	concatened_string = *splited_string;
	while (splited_string[len] != NULL)
		len++;
	while (i < len)
	{
		concatened_string = ft_strjoin(concatened_string, splited_string[i]);
		i++;
	}
	return (concatened_string);
}

char	*concat_chain_to_string(t_lexer_node *first_node)
{
	char			*concatened_string;
	t_lexer_node	*current_node;

	while (first_node && first_node->word == NULL)
		first_node = first_node->next;
	if (!first_node)
	 	return (NULL);
	concatened_string = first_node->word;
	current_node = first_node->next;
	while (current_node != NULL)
	{
		if (current_node->word != NULL)
			concatened_string = ft_strjoin(concatened_string, current_node->word);
		current_node = current_node->next;
	}
	return (concatened_string);
}