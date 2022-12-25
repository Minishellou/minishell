/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:14:28 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/25 19:43:37 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
int	get_redir_type(char *str)
{
	if (str[1] && str[1] == LESS)
		return (LESSER);
	if (str[1] && str[1] == GREAT)
		return (GREATER);
	if (str[0] == LESS)
		return (LESS);
	if (str[0] == GREAT)
		return (GREAT);
	return (ERROR);
}

static
t_lexer_node	*create_redir_node(char *str)
{
	int				redir_type;
	t_lexer_node	*new_redir_node;

	new_redir_node = NULL;
	redir_type = get_redir_type(str);
	if (redir_type == LESSER)
		new_redir_node = (t_lexer_node *)create_lexer_node("<<");
	if (redir_type == GREATER)
		new_redir_node = (t_lexer_node *)create_lexer_node(">>");
	if (redir_type == LESS)
		new_redir_node = (t_lexer_node *)create_lexer_node("<");
	if (redir_type == GREAT)
		new_redir_node = (t_lexer_node *)create_lexer_node(">");
	return (new_redir_node);
}

static
char	*copy_word_until_redirection(char *str)
{
	int		len;
	char	*buffer;

	len = 0;
	if (!str)
		return (NULL);
	while (str[len] && (is_special_token(str[len]) == ERROR))
		len++;
	buffer = ft_malloc(len + 1);
	if (!buffer)
		return (NULL);
	buffer[len] = '\0';
	while (len-- != 0)
		buffer[len] = str[len];
	return (buffer);
}

t_lexer_node	*split_word_on_redir(t_lexer_node *current_node)
{
	int				i;
	char			*new_word;
	char			*current_word;
	t_lexer_node	*new_node;
	t_lexer_node	*parsed_word;
	t_lexer_node	*new_redirection;

	i = 0;
	parsed_word = NULL;
	current_word = current_node->word;
	while (current_word[i])
	{
		if (is_special_token(current_word[i]) == SUCCESS)
		{
			new_redirection = create_redir_node(&current_word[i]);
			if (new_redirection == NULL)
				return (NULL);
			append_to_chain((t_node **)&parsed_word, (t_node *)new_redirection);
		}
		while (current_word[i] && is_special_token(current_word[i]) == SUCCESS)
			i++;
		if (current_word[i])
		{
			new_word = copy_word_until_redirection(&current_word[i]);
			new_node = (t_lexer_node *)create_lexer_node(new_word);
			if (new_word == NULL || new_node == NULL)
				return (NULL);
			append_to_chain((t_node **)&parsed_word, (t_node *)new_node);
		}
		while (current_word[i] && is_special_token(current_word[i]) != SUCCESS)
			i++;
	}
	return (parsed_word);
}

//	Vladimir
static
int	put_in(t_lexer_node *to_replace, t_lexer_node *subchain)
{
	int				i;
	t_lexer_node	*next_node;
	t_lexer_node	*last_subchain_node;

	i = 0;
	next_node = to_replace->next;
	if (subchain->next != NULL)
		to_replace->next = subchain->next;
	to_replace->word = subchain->word;
	last_subchain_node = subchain;
	while (last_subchain_node->next)
	{
		last_subchain_node = last_subchain_node->next;
		i++;
	}
	last_subchain_node->next = next_node;
	return (i);
}

int	parse_redir_in_command_expression(t_lexer_node **command_expression)
{
	int				to_the_next_word;
	t_lexer_node	*splited_word;
	t_lexer_node	*current_node;

	current_node = *command_expression;
	while (current_node)
	{	
		if ((ft_strchr(current_node->word, LESS) || ft_strchr(current_node->word, GREAT)) \
			&& ft_strlen(current_node->word) != 1)
		{
			splited_word = split_word_on_redir(current_node);
			if (!splited_word)
				return (ERROR);
			to_the_next_word = put_in(current_node, splited_word);
			while (to_the_next_word--)
				current_node = current_node->next;
		}
		current_node = current_node->next;
	}
	return (SUCCESS);
}
