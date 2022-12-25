/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:14:28 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/25 19:06:01 by mcorso           ###   ########.fr       */
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
	int		i;
	int		len;
	char	*buffer;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len] && (is_special_token(str[len]) == ERROR))
		len++;
	i = 0;
	buffer = ft_malloc(len + 1);
	if (!buffer)
		return (NULL);
	while (i < len)
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i] = '\0';
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
int	put_in(t_lexer_node *current, t_lexer_node *put_in)
{
	t_lexer_node	*next;
	t_lexer_node	*last_put_in;
	int				i;

	i = 0;
	last_put_in = put_in;
	next = current->next;
	current->next = put_in->next;
	current->word = put_in->word;
	while (last_put_in->next)
	{
		last_put_in = last_put_in->next;
		i++;
	}
	last_put_in->next = next;
	return (i);
}

int	parse_redir_in_command_expression(t_lexer_node **command_expression)
{
	int				word_len;
	int				to_the_next_word;
	t_lexer_node	*splited_word;
	t_lexer_node	*current_node;

	current_node = *command_expression;
	while (current_node)
	{	
		word_len = ft_strlen(current_node->word);
		if (!ft_strncmp(current_node->word, "<<", word_len) || \
			!ft_strncmp(current_node->word, ">>", word_len))
		{
			current_node = current_node->next;
			continue ;
		}
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
