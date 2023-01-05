/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:29:59 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/05 15:44:27 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_chain_len(t_node *chain);

t_node	*make_chain_from_array(char **array, t_node_creator create_node)
{
	int		i;
	t_node	**new_node;
	t_node	*first_node;

	i = 0;
	first_node = NULL;
	if (array[0])
		first_node = create_node(array[i++]);
	if (first_node == NULL)
		return (NULL);
	new_node = &first_node->next;
	while (array[i] != NULL)
	{
		*new_node = create_node(array[i++]);
		if (*new_node == NULL)
			return (NULL);
		new_node = &(*new_node)->next;
	}
	return (first_node);
}

char	**make_array_from_chain(t_node *chain, t_node_getter get_node_value)
{
	int		index;
	int		number_of_node;
	char	*current_node_value;
	char	**ret_array;

	number_of_node = get_chain_len(chain);
	ret_array = ft_malloc(sizeof(*ret_array) * (number_of_node + 1));
	if (!ret_array)
		return (NULL);
	index = 0;
	while (index < number_of_node)
	{
		current_node_value = get_node_value(chain);
		if (!current_node_value)
			return (NULL);
		ret_array[index++] = current_node_value;
		chain = chain->next;
	}
	ret_array[index] = NULL;
	return (ret_array);
}

t_node	*last_node(t_node *current_node)
{
	if (!current_node)
		return (NULL);
	while (current_node->next)
		current_node = current_node->next;
	return (current_node);
}

void	append_to_chain(t_node **node, t_node *new_node)
{
	t_node	*last;

	if (!node)
		return ;
	if (*node)
	{
		last = last_node(*node);
		last->next = new_node;
	}
	else
		*node = new_node;
}

static int	get_chain_len(t_node *chain)
{
	int	number_of_node;

	number_of_node = 0;
	while (chain && ++number_of_node)
		chain = chain->next;
	return (number_of_node);
}
