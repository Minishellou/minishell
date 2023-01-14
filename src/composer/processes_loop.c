/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:53:30 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/14 13:18:01 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec_node	*redir_process_loop(t_exec_node *execute_chain,
		t_lexer_node **lexer_output)
{
	while (*lexer_output && (*lexer_output)->token != PIPE)
	{
		if ((*lexer_output)->token != WORD)
		{
			execute_chain->redir_chain = parse_redirection(execute_chain,
					*lexer_output);
			if (!(execute_chain)->redir_chain)
				return (NULL);
			*lexer_output = (*lexer_output)->next;
		}
		else
		{
			execute_chain = command_output_context(execute_chain, lexer_output);
			if (!execute_chain)
				return (NULL);
		}
		if (*lexer_output)
			*lexer_output = (*lexer_output)->next;
	}
	return (execute_chain);
}

t_exec_node	*command_process_loop(t_exec_node *execute_chain,
		t_lexer_node **lexer_output)
{
	while ((*lexer_output != NULL) && (*lexer_output)->token != PIPE)
	{
		if ((*lexer_output)->token != WORD)
		{
			execute_chain->redir_chain = parse_redirection(execute_chain,
					*lexer_output);
			if (!execute_chain->redir_chain)
				return (NULL);
			*lexer_output = (*lexer_output)->next;
		}
		else
		{
			execute_chain->arg_chain = add_argument(execute_chain,
					(*lexer_output)->word);
			if (!execute_chain->arg_chain)
				return (NULL);
		}
		if (*lexer_output)
			*lexer_output = (*lexer_output)->next;
	}
	return (execute_chain);
}
