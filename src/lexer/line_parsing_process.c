/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:46:38 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/25 19:10:42 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_lexer_node	*make_chain_of_command(char *input);
static t_lexer_node	*parse_simple_command(t_lexer_node *cmd);

t_lexer_node	*lexer_line_parsing_process(char *command_line)
{
	t_node			*output_chain;
	t_lexer_node	*command_list;
	t_lexer_node	*parsed_command;

	output_chain = NULL;
	if (ft_strchr(command_line, PIPE))
		command_list = make_chain_of_command(command_line);
	else
		command_list = (t_lexer_node *)create_lexer_node(command_line);
	if (command_list == NULL)
		return (NULL);
	while (command_list)
	{
		parsed_command = parse_simple_command(command_list);
		if (command_list->next)
			append_to_chain((t_node **)&parsed_command, create_lexer_node("|"));
		append_to_chain((t_node **)&output_chain, (t_node *)parsed_command);
		command_list = command_list->next;
	}
	return ((t_lexer_node *)output_chain);
}

static t_lexer_node	*parse_simple_command(t_lexer_node *cmd)
{
	char			**split;
	t_lexer_node	*command_expression;

	split = ft_lexer_split(cmd->word);
	if (!split)
		return (NULL);
	command_expression = \
		(t_lexer_node *)make_chain_from_array(split, create_lexer_node);
	if (!command_expression)
		return (NULL);
	parse_redir_in_command_expression(&command_expression);
	if (!command_expression)
		return (NULL);
	return (command_expression);
}

static t_lexer_node	*make_chain_of_command(char *input)
{
	char			**words;
	t_lexer_node	*node_pipe;

	words = ft_split(input, PIPE);
	node_pipe = (t_lexer_node *)make_chain_from_array(words, create_lexer_node);
	return (node_pipe);
}
