/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 11:42:24 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer_node	*command_expression(t_lexer_node *cmd)
{
	char			**split;
	t_lexer_node 	*command_expression;
	

	//printf("cmd->word = %s\n", cmd->word);
	split = ft_split(cmd->word);
	if (!split)
		return (NULL);
	command_expression = (t_lexer_node*)make_chain_from_array(split, create_lexer_node);
	if (!command_expression)
		return (NULL);
	str_to_lexer_node(&command_expression);
	if (!command_expression)
		return (NULL);
	return (command_expression);
}

void 	add_command_to_lexer_output(t_lexer_node *first_node)
{
	t_lexer_node	*tmp_node;
	
	if (!g_glo.lexer_output_chain)
		g_glo.lexer_output_chain = first_node;
	else
	{
		tmp_node = (t_lexer_node *)last_node((t_node *)g_glo.lexer_output_chain);
		tmp_node->next = first_node;
	}
}

void tokenizer(void)
{
	t_lexer_node *tmp;
	int 		word_len;

	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		word_len = ft_strlen(tmp->word);
		if (!ft_strncmp(tmp->word, "|", word_len))
			tmp->token = PIPE;
		else if (!ft_strncmp(tmp->word, "<", word_len))
			tmp->token = LESS;
	 	else if (!ft_strncmp(tmp->word, ">", word_len))
			tmp->token = GREAT;
		else if(!ft_strncmp(tmp->word, "<<", word_len))
			tmp->token = LESSER;
		else if (!ft_strncmp(tmp->word, ">>", word_len))
			tmp->token = GREATER;
		else 
			tmp->token = 10;
		tmp = tmp->next;
	}
}

int lexer(char *input)
{
	t_lexer_node	*command_list;

	if (quote_neon(&input) != SUCCESS)
		return (ERROR);
	if (parse_token(input) != SUCCESS)
		return (ERROR);
	if (ft_strchr(input, PIPE))
	{
		command_list = process_spipe(input);
		if (command_list == NULL)
			return (ERROR);
	}
	else
		command_list = (t_lexer_node *)create_lexer_node(input);
	fill_lexer_output(command_list);
	tokenizer();
	if (chain_parse() != SUCCESS)
	{
		return (ERROR);
	}
	return (SUCCESS);
}