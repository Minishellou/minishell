/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:14:28 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/14 14:01:03 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_redir_to_chain(t_lexer_node **chain, char *current_word)
{
	t_lexer_node	*new_redirection;

	new_redirection = create_redir_node(current_word);
	if (new_redirection == NULL)
		return (ERROR);
	append_to_chain((t_node **)chain, (t_node *)new_redirection);
	return (SUCCESS);
}

static int	add_word_to_chain(t_lexer_node **chain, char *current_word)
{
	char			*new_word;
	t_lexer_node	*new_node;

	new_word = copy_word_until_redirection(current_word);
	new_node = (t_lexer_node *)create_lexer_node(new_word);
	if (new_word == NULL || new_node == NULL)
		return (ERROR);
	append_to_chain((t_node **)&chain, (t_node *)new_node);
	return (SUCCESS);
}

t_lexer_node	*isolate_redir_in_subchain(t_lexer_node *current_node)
{
	int				i;
	char			*current_word;
	t_lexer_node	*parsed_word;

	i = 0;
	parsed_word = NULL;
	current_word = current_node->word;
	while (current_word[i])
	{
		if (is_special_token(current_word[i]) == SUCCESS)
			if (add_redir_to_chain(&parsed_word, &current_word[i]) != SUCCESS)
				return (NULL);
		while (current_word[i] && is_special_token(current_word[i]) == SUCCESS)
			i++;
		if (current_word[i])
			if (add_word_to_chain(&parsed_word, &current_word[i]) != SUCCESS)
				return (NULL);
		while (current_word[i] && is_special_token(current_word[i]) != SUCCESS)
			i++;
	}
	return (parsed_word);
}

int	parse_redir_in_command_expression(t_lexer_node **command_expression)
{
	int				to_the_next_word;
	t_lexer_node	*redir_subchain;
	t_lexer_node	*current_node;

	current_node = *command_expression;
	while (current_node)
	{
		if ((ft_strchr(current_node->word, LESS)
				|| ft_strchr(current_node->word, GREAT))
			&& ft_strlen(current_node->word) != 1)
		{
			redir_subchain = isolate_redir_in_subchain(current_node);
			if (!redir_subchain)
				return (ERROR);
			to_the_next_word = replace_and_track_next_node(current_node, \
															redir_subchain);
			while (to_the_next_word--)
				current_node = current_node->next;
		}
		current_node = current_node->next;
	}
	return (SUCCESS);
}
