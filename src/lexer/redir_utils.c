/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:43:02 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/26 13:47:10 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer_node	*create_redir_node(char *str)
{
	t_lexer_node	*new_redir_node;

	new_redir_node = NULL;
	if (str[1] && str[1] == LESS)
		new_redir_node = (t_lexer_node *)create_lexer_node("<<");
	else if (str[0] == LESS)
		new_redir_node = (t_lexer_node *)create_lexer_node("<");
	if (str[1] && str[1] == GREAT)
		new_redir_node = (t_lexer_node *)create_lexer_node(">>");
	else if (str[0] == GREAT)
		new_redir_node = (t_lexer_node *)create_lexer_node(">");
	return (new_redir_node);
}

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

int	replace_and_track_next_node(t_lexer_node *to_replace, \
								t_lexer_node *subchain)
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
