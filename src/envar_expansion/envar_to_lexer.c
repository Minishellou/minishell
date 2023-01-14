/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_to_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:21:36 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/14 19:29:17 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_lexer_node	*add_env_word(char *word)
{
	char			*buffer;
	t_lexer_node	*env_word;
	int				len;
	int				i;

	len = 1;
	i = 1;
	if (!word)
		return (NULL);
	while (word[len] && (ft_isalnum(word[len]) || word[len] == '?'))
		len++;
	buffer = ft_malloc(len + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '$';
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '?'))
	{
		buffer[i] = word[i];
		i++;
	}
	buffer[i] = '\0';
	env_word = (t_lexer_node *)create_lexer_node(buffer);
	if (!env_word)
		return (NULL);
	return (env_word);
}

static t_lexer_node	*add_regular_word(char *word)
{
	char			*buffer;
	t_lexer_node	*regular_word;
	int				len;
	int				i;

	i = 0;
	len = 0;
	if (!word)
		return (NULL);
	while (word[len] && word[len] != '$')
		len++;
	buffer = ft_malloc(len + 1);
	if (!buffer)
		return (NULL);
	while (word[i] && word[i] != '$')
	{
		buffer[i] = word[i];
		i++;
	}
	buffer[i] = '\0';
	regular_word = (t_lexer_node *)create_lexer_node(buffer);
	if (!regular_word)
		return (NULL);
	return (regular_word);
}

static t_lexer_node	*add_node_unit(char *str)
{
	if (!str)
		return (NULL);
	if (str[0] == '$')
		return (add_env_word(str));
	return (add_regular_word(str));
}

t_lexer_node	*add_env_list(char *word, t_lexer_node *node)
{
	t_lexer_node	*tmp;

	tmp = NULL;
	if (!node)
	{
		node = add_node_unit(word);
		if (!node)
			return (NULL);
		return (node);
	}
	tmp = node;
	node = (t_lexer_node *)last_node((t_node *)node);
	node->next = add_node_unit(word);
	if (!node->next)
		return (NULL);
	return (tmp);
}

t_lexer_node	*lexer_envar(char *env_node)
{
	t_lexer_node	*node;
	int				i;

	i = 0;
	node = NULL;
	if (!env_node)
		return (NULL);
	while (env_node[i])
	{
		if ((check_and_add_var(env_node, &node, &i)) != SUCCESS)
			return (NULL);
	}
	return (node);
}
