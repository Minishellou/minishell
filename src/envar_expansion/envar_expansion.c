/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:46:54 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/22 12:22:05 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*get_envar(char *envar_name)
{
	size_t		envar_name_len;
	t_env_node	env;
	t_env_node	*current_node;

	env.next = g_glo.env;
	current_node = &env;
	envar_name_len = ft_strlen(envar_name) - 1;
	while (1)
	{
		current_node = current_node->next;
		if (!current_node)
			break ;
		if (ft_strncmp(current_node->name, envar_name + 1, envar_name_len))
			continue;
		if (envar_name_len != ft_strlen(current_node->name))
			continue;
		break ;
	}
	return (current_node);
}

static t_lexer_node	**find_envar_node(t_lexer_node **first_node)
{
	t_lexer_node	*current_node;
	t_lexer_node	**ret_node;

	current_node = *first_node;
	if (*(*first_node)->word == '$')
		return (first_node);
	while (*current_node->next->word != '$')
		current_node = current_node->next;
	ret_node = &current_node->next;
	return (ret_node);
}

int	expand_and_add_to_string(char **current_string, t_env_node *envar)
{
	char			**splited_string;
	t_lexer_node	*first_node;
	t_lexer_node	**envar_node;

	splited_string = ft_split(*current_string, ' ');
	first_node = (t_lexer_node *)make_chain_from_array(splited_string, create_lexer_node);
	envar_node = find_envar_node(&first_node);
	if (expand_and_add_to_chain(envar_node, envar) != SUCCESS)
		return (ERROR);
	*current_string = concat_chain_to_string(first_node);
	if (!*current_string)
		return (ERROR);
	return (SUCCESS); 
}

int	expand_and_add_to_chain(t_lexer_node **envar_node, t_env_node *envar)
{
	char			**splited_envar;
	t_lexer_node	*subchain;

	subchain = NULL;
	if (envar)
		splited_envar = ft_split(envar->value, ' ');
	if (envar && splited_envar)
		subchain = (t_lexer_node *)make_chain_from_array(splited_envar, create_lexer_node);
	if (!envar)
		subchain = (t_lexer_node *)create_lexer_node(NULL);
	if (!subchain)
		return (ERROR);
	include_subchain_at((t_node **)envar_node, (t_node *)subchain);
	return (SUCCESS);	
}
