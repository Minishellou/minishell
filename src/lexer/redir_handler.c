/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:14:28 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 16:07:43 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
int	which_redir(char *str)
{
	if (str[1] == LESS)
		return (LESSER);
	if (str[1] == GREAT)
		return (GREATER);
	if (str[0] == LESS)
		return (LESS);
	if (str[0] == GREAT)
		return (GREAT);
	return (ERROR);
}

static
t_lexer_node	*create_redir(char *str)
{
	t_lexer_node	*redir;

	redir = NULL;
	if (which_redir(str) == LESSER)
		redir = (t_lexer_node *)create_lexer_node("<<");
	else if (which_redir(str) == GREATER)
		redir = (t_lexer_node *)create_lexer_node(">>");
	if (which_redir(str) == LESS)
		redir = (t_lexer_node *)create_lexer_node("<");
	if (which_redir(str) == GREAT)
		redir = (t_lexer_node *)create_lexer_node(">");
	return (redir);
}

static
char	*ft_cpy(char *str)
{
	char	*buffer;
	int		i;
	int		len;

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

t_lexer_node	*split_redir(t_lexer_node *tmp)
{
	t_lexer_node	*lst;
	char			*word;
	int				i;
	t_lexer_node	*redir;

	i = 0;
	word = tmp->word;
	lst = NULL;
	while (word[i])
	{
		if (is_special_token(word[i]) == SUCCESS)
		{
			redir = create_redir(&word[i]);
			lex_addback(&lst, redir);
		}
		while (word[i] && is_special_token(word[i]) == SUCCESS)
			i++;
		if (word[i])
			lex_addback(&lst, \
				(t_lexer_node *)create_lexer_node(ft_cpy(&word[i])));
		while (word[i] && is_special_token(word[i]) != SUCCESS)
			i++;
	}
	return (lst);
}

static
int	ft_put_in(t_lexer_node *current, t_lexer_node *put_in)
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

void	str_to_lexer_node(t_lexer_node **command_expression)
{
	t_lexer_node	*tmp;
	int				i;
	int				word_len;

	tmp = *command_expression;
	while (tmp)
	{	
		i = 0;
		word_len = ft_strlen(tmp->word);
		if (!ft_strncmp(tmp->word, "<<", word_len) || \
			!ft_strncmp(tmp->word, ">>", word_len))
		{
			tmp = tmp->next;
			continue ;
		}
		if ((ft_strchr(tmp->word, LESS) || ft_strchr(tmp->word, GREAT)) \
			&& ft_strlen(tmp->word) != 1)
		{
			i = ft_put_in(tmp, split_redir(tmp));
			while (i--)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}
