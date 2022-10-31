/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:01:49 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/31 12:57:59 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
t_env_node	new_env_node(char *env_var)
{
	char		**name_value;
	t_env_node	new_node;

	name_value = ft_split(env_var, "=");
	new_node = ft_malloc(sizeof(*new_node));
	new_node.name = name_value[0];
	new_node.value = name_value[1];
	new_node.next = NULL;
	return (new_node);
}

static
t_env_node	*make_env_chain(t_env_node *current_node, char *current_element, \
							int return_first)
{
	if (*current_array_element == NULL)
		return (NULL);
	current_node = new_env_node(current_array_element);
	make_env_chain(curren_node->next, current_array_element++, 0);
	if (return_first)
		return (current_node);
}

void	init_global(char **envp)
{
	size_t	size_of_redir_table;

	global.standard_input = dup(0);
	global.standard_output = dup(1);
	global.env = make_env_to_chain(global.env, *envp, 1);
	global.garbage_ctr = NULL;
	global.redirection_table = NULL;
	global.lexer_output_chain = NULL;
	global.execution_chain = NULL;
}
