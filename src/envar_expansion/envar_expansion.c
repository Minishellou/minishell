/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:46:54 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/09 12:54:33 by gkitoko          ###   ########.fr       */
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

static t_lexer_node	*find_envar_node(t_lexer_node *first_node)
{
	t_lexer_node	*current_node;
	t_lexer_node	*ret_node;

	current_node = first_node;
	while (!has_envar(current_node->word))
		current_node = current_node->next;
	return (current_node);
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
