/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:46:39 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/16 11:30:41 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec_node	*redirection_output_context(t_exec_node *execute_chain,
										t_lexer_node **lexer_output)
{
	if (!(execute_chain))
	{
		execute_chain = (t_exec_node *)create_exec_node(NULL);
		if (!(execute_chain))
			return (NULL);
		(execute_chain)->arg_chain = NULL;
		(execute_chain)->redir_chain = NULL;
	}
	(execute_chain)->redir_chain = parse_redirection(execute_chain, \
													*lexer_output);
	if (!(execute_chain)->redir_chain)
		return (NULL);
	*lexer_output = (*lexer_output)->next->next;
	execute_chain = redir_process_loop(execute_chain, lexer_output);
	return (execute_chain);
}

t_exec_node	*command_output_context(t_exec_node *execute_chain,
									t_lexer_node **lexer_output)
{
	if (!(execute_chain))
	{
		execute_chain = (t_exec_node *)create_exec_node((*lexer_output)->word);
		(execute_chain)->redir_chain = NULL;
		(execute_chain)->arg_chain = NULL;
	}
	else
		(execute_chain)->command_path = (*lexer_output)->word;
	*lexer_output = (*lexer_output)->next;
	execute_chain = command_process_loop(execute_chain, lexer_output);
	return (execute_chain);
}

t_exec_node	*composer_process(t_lexer_node **lexer_output_chain)
{
	t_exec_node	*execute_chain;

	execute_chain = NULL;
	if (!(*lexer_output_chain))
		return (NULL);
	if ((*lexer_output_chain)->token != WORD)
		execute_chain = redirection_output_context(execute_chain,
				lexer_output_chain);
	else
		execute_chain = command_output_context(execute_chain,
				lexer_output_chain);
	return (execute_chain);
}

t_exec_node	*composer(void)
{
	t_lexer_node	*tmp;
	t_exec_node		*execute_chain;

	execute_chain = NULL;
	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		execute_chain = add_process(&tmp, execute_chain);
		if (!execute_chain)
			return (NULL);
		if (tmp)
			tmp = tmp->next;
	}
	return (execute_chain);
}

// void printf_execute_chain(t_exec_node *node)
// {
// 	t_exec_node *tmp;
// 	if (!node)
// 		return ;
// 	tmp = node;
// 	while (tmp)
// 	{
// 		if (tmp->command_path)
// 		{
// 			printf("\n____COMMAND_PATH____\n");
// 			printf("Command Path -> %s\n", tmp->command_path);
// 		}
// 		if (tmp->arg_chain)
// 		{
// 			printf("\n____ARG_CHAIN____\n");
// 			print_word_list(tmp->arg_chain);
// 		}
// 		if (tmp->redir_chain)
// 		{
// 			printf("\n____REDICTION____\n");
// 			printf_redir_chain(tmp->redir_chain);
// 		}
// 		tmp = tmp->next;
// 	}
// }