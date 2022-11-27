/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/27 14:42:30 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void quote_rehestablish(char *str)
{
	int i;

	if (!str)
		return ; 
	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

int	command_expression(t_lexer_node **cmd, char *last_node)
{
	char			**split;
	t_lexer_node 	*command_expression;
	
	split = ft_split((*cmd)->word);
	if (!split)
		return (ERROR);
	command_expression = (t_lexer_node*)make_chain_from_array(split, create_lexer_node);
	if (!command_expression)
		return (ERROR);
	while (command_expression->next)
		command_expression = command_expression->next;
	if (last_node != NULL)
	{
		command_expression = (t_lexer_node *)create_lexer_node(last_node);
		if (!command_expression)
			return (ERROR);
		command_expression = command_expression->next;
	}
	// waiting for subchain_at
	return(SUCCESS);
}
 
int	process_spipe(char *input)
{
	char	**words;
	int		i;
	t_lexer_node *command_spipe;
	
	i = 0;
	if(quote_neon(&input) != SUCCESS)
		return (ERROR);
	if(parse_token(input) != SUCCESS)
		return (ERROR);
	words = ft_split_target(input, '|');
	while (words[i])
	{
		if (words[i][0] == ' ' && ft_strlen(words[i]) <= 2)
			return (ERROR);
		quote_neon(&words[i++]);
	}
	i = 0;
	while (words[i])
		quote_rehestablish(words[i++]);
	command_spipe = (t_lexer_node *)make_chain_from_array(words, create_lexer_node);
	return (SUCCESS);
}