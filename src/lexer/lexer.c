/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/01 19:03:37 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer_node	*command_expression(t_lexer_node *cmd, char *last_token)
{
	char			**split;
	t_lexer_node 	*command_expression;
	t_lexer_node	*tmp_node;
	
	if (quote_neon(&cmd->word) != SUCCESS)
		return (NULL);
	split = ft_split(cmd->word);
	if (!split)
		return (NULL);
	if (array_to_rehestablish(&split) != SUCCESS)
		return (NULL);
	tmp_node = NULL;
	command_expression = (t_lexer_node*)make_chain_from_array(split, create_lexer_node);
	if (!command_expression)
		return (NULL);
	tmp_node = command_expression;
	tmp_node = (t_lexer_node *)last_node((t_node *)tmp_node);
	if (last_token)
		(tmp_node)->next = (t_lexer_node *)create_lexer_node(last_token);
	return (command_expression);
}

static
void 	add_token_to_chain(t_lexer_node *tmp, t_lexer_node *tmp2, char *token)
{
	while (tmp->next)
	{
		if (!g_glo.lexer_output_chain)
		{
			g_glo.lexer_output_chain = command_expression(tmp, token);
			tmp2 = g_glo.lexer_output_chain;
		}
		else
			tmp2->next = command_expression(tmp, token);
		tmp2 = (t_lexer_node *)last_node((t_node *)tmp2);
		tmp = tmp->next;
	}
	tmp2->next = command_expression(tmp, NULL);
}

static
int	process_spipe(char *input)
{
	char	**words;
	t_lexer_node *tmp;
	t_lexer_node *tmp2;
	t_lexer_node *node_pipe;

	tmp2 = NULL;
	if(quote_neon(&input) != SUCCESS)
		return (ERROR);
	if(parse_token(input) != SUCCESS)
		return (ERROR);
	words = ft_split_target(input, '|');
	if (array_to_rehestablish(&words) != SUCCESS)
		return (ERROR);
	node_pipe = (t_lexer_node *)make_chain_from_array(words, create_lexer_node);
	tmp = node_pipe;
	add_token_to_chain(tmp, tmp2, "PIPE");
	return (SUCCESS);
}

int lexer(char *input)
{
	if (process_spipe(input) != SUCCESS)
		return (ERROR);
	return (SUCCESS);	
}