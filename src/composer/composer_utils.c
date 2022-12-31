/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:02:03 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/31 21:36:11 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer_node *add_argument(t_exec_node *node, char *word)
{
	t_lexer_node *tmp;

	tmp = NULL;
	if (!word)
		return (NULL);	
	if (!node->arg_chain) 
	{
		node->arg_chain = (t_lexer_node *)create_lexer_node(word);
		return (node->arg_chain);
	}
	else
	{	
		tmp = node->arg_chain;
		node->arg_chain = (t_lexer_node *)last_node((t_node *)node->arg_chain);
		node->arg_chain->next = (t_lexer_node *)create_lexer_node(word);
	}
	return (tmp);
}

t_exec_node *redirection_composer_unit(t_exec_node **execute_chain, t_lexer_node **lexer_output)
{
	*execute_chain = (t_exec_node*)create_exec_node(NULL);
	(*execute_chain)->arg_chain = NULL;
	(*execute_chain)->redir_chain = NULL;
	if (!(*execute_chain))
		return (NULL);
	(*execute_chain)->redir_chain = parse_redirection((*execute_chain), (*lexer_output));
	return (*execute_chain);
}

t_exec_node *command_path_composer_unit(t_exec_node **execute_chain, t_lexer_node **lexer_output)
{
	*execute_chain = (t_exec_node *)create_exec_node((*lexer_output)->word);
	(*execute_chain)->redir_chain = NULL;
	(*execute_chain)->arg_chain = NULL;
	*lexer_output = (*lexer_output)->next;
	while (*lexer_output != NULL && (*lexer_output)->token != PIPE)
	{
		if ((*lexer_output)->token != 10)
		{
			(*execute_chain)->redir_chain = parse_redirection(*execute_chain, *lexer_output);
			*lexer_output = (*lexer_output)->next;
		}
		else
			(*execute_chain)->arg_chain = add_argument(*execute_chain, (*lexer_output)->word);
		*lexer_output = (*lexer_output)->next;
	}
	return (*execute_chain);
}

t_redirection *parse_redirection(t_exec_node *node, t_lexer_node *output_chain)
{
	t_exec_node *tmp;
	
	tmp = node;
	if (!node)
		return (NULL);
	node->redir_chain = ft_malloc(sizeof(t_redirection));
	if (!node->redir_chain)
		return(NULL);
	node->redir_chain->next = NULL;
	node->redir_chain->argument = output_chain->next->word;
	if (output_chain->token == '<')
		node->redir_chain->type = INPUT;
	else if (output_chain->token == '>')
		node->redir_chain->type = OUTPUT;
	else if (output_chain->token == 4)
		node->redir_chain->type = APPEND;
	else if (output_chain->token == 5)
		node->redir_chain->type = HEREDOC;
	return (node->redir_chain);
}

