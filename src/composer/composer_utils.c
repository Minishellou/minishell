/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:02:03 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/16 19:05:06 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec_node	*add_process(t_lexer_node **output_chain, t_exec_node *node)
{
	t_exec_node	*tmp;

	tmp = NULL;
	if (!(*output_chain))
		return (NULL);
	if (!node)
	{
		node = composer_process(output_chain);
		if (!node)
			return (NULL);
		return (node);
	}
	tmp = node;
	node = (t_exec_node *)last_node((t_node *)node);
	node->next = composer_process(output_chain);
	if (!node->next)
		return (NULL);
	return (tmp);
}

t_lexer_node	*add_argument(t_exec_node *node, char *word)
{
	t_lexer_node	*tmp;

	tmp = NULL;
	if (!node->arg_chain)
	{
		node->arg_chain = (t_lexer_node *)create_lexer_node(word);
		if (!node->arg_chain)
			return (NULL);
		return (node->arg_chain);
	}
	tmp = node->arg_chain;
	node->arg_chain = (t_lexer_node *)last_node((t_node *)node->arg_chain);
	node->arg_chain->next = (t_lexer_node *)create_lexer_node(word);
	if (!node->arg_chain->next)
		return (NULL);
	return (tmp);
}

t_redirection	*create_parse_redirection(t_lexer_node *output_chain)
{
	t_redirection	*node_redirection;

	node_redirection = ft_malloc(sizeof(t_redirection));
	if (!node_redirection)
		return (NULL);
	node_redirection->next = NULL;
	node_redirection->argument = output_chain->next->word;
	if (output_chain->token == LESS)
		node_redirection->type = INPUT;
	else if (output_chain->token == GREAT)
		node_redirection->type = OUTPUT;
	else if (output_chain->token == LESSER)
		node_redirection->type = HEREDOC;
	else if (output_chain->token == GREATER)
		node_redirection->type = APPEND;
	return (node_redirection);
}

t_redirection	*parse_redirection(t_exec_node *node,
		t_lexer_node *output_chain)
{
	t_redirection	*tmp;

	tmp = NULL;
	if (!node || !output_chain)
		return (NULL);
	if (!node->redir_chain)
	{
		node->redir_chain = create_parse_redirection(output_chain);
		if (!node->redir_chain)
			return (NULL);
		return (node->redir_chain);
	}
	tmp = node->redir_chain;
	node->redir_chain = (t_redirection *)last_node((t_node *)node->redir_chain);
	node->redir_chain->next = create_parse_redirection(output_chain);
	if (!node->redir_chain)
		return (NULL);
	return (tmp);
}
