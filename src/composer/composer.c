/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:46:39 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/31 20:30:06 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
t_lexer_node *eol_or_pipe(t_lexer_node *node)
{
	t_lexer_node *tmp;

	if (!node)
		return (NULL);
	tmp = node;
	while (tmp != NULL && tmp->token != PIPE)
		tmp = tmp->next;
	return (tmp);
}

t_exec_node *composer_process(t_lexer_node *lexer_output_chain)
{
	t_lexer_node *tmp;
	t_exec_node *execute_chain;

	if (!lexer_output_chain)
		return (NULL);
	execute_chain = NULL;
	tmp = lexer_output_chain;
	if (tmp->token != 10)
		execute_chain = redirection_composer_unit(&execute_chain, &tmp);
	else
		execute_chain = command_path_composer_unit(&execute_chain, &tmp);
	return (execute_chain);
}

t_exec_node *composer(void)
{
	t_lexer_node *tmp;
	t_exec_node *execute_chain;
	t_exec_node *tmp2;

	execute_chain = NULL;
	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		if (execute_chain == NULL)
		{
			if (tmp->token != 10)
			{
				execute_chain = composer_process(tmp);
				tmp2 = execute_chain;
				tmp = tmp->next->next;
			} else 
			{
				execute_chain = composer_process(tmp);
				tmp2 = execute_chain;
				if(!(tmp = eol_or_pipe(tmp)))
					break ;
				tmp = tmp->next;
			}
		}
		else
		{
			if (tmp->token !=  10)
			{
				tmp2->next = composer_process(tmp);
				tmp = tmp->next->next;
				tmp2 = tmp2->next;
			}
			else 
			{
				tmp2->next = composer_process(tmp);
				tmp2 = tmp2->next;
				if (!(tmp = eol_or_pipe(tmp)))
					break;
				tmp = tmp->next;
			}
		}
	}
	return (execute_chain);
}

void printf_execute_chain(t_exec_node *node)
{
	t_exec_node *tmp;
	if (!node)
		return ;
	tmp = node;
	while (tmp)
	{	
		if (tmp->command_path)
		{
			printf("\n____COMMAND_PATH____\n");
			printf("Command Path -> %s\n", tmp->command_path);	
		}
		if (tmp->arg_chain)
		{
			printf("\n____ARG_CHAIN____\n");
			print_word_list(tmp->arg_chain);
		}
		if (tmp->redir_chain)
		{
			printf("\n____REDICTION____\n");
			printf_redir_chain(tmp->redir_chain);
		}
		tmp = tmp->next;
	}
}