/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:46:38 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 11:36:17 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer_node	*process_spipe(char *input)
{
	char	**words;
	t_lexer_node *node_pipe;

	words = ft_split_target(input, PIPE);
	node_pipe = (t_lexer_node *)make_chain_from_array(words, create_lexer_node);
	return (node_pipe);
}

void	fill_lexer_output(t_lexer_node *command_list)
{
	t_lexer_node *parsed_command;
	t_lexer_node *last_parsed_node;
	
	while (command_list)
	{
		parsed_command = command_expression(command_list);
		if (command_list->next)
		{
			last_parsed_node = (t_lexer_node *)last_node((t_node *)parsed_command);
			last_parsed_node->next = (t_lexer_node *)create_lexer_node("|");
		}
		add_command_to_lexer_output(parsed_command);
		command_list = command_list->next;
	}
}