/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:46:54 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/21 13:48:29 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*get_envar(char *envar_name)
{
	t_env_node	*env_node;

	env_node = g_glo.env;
	while (env_node && \
			ft_strncmp(env_node->name, envar_name + 1, ft_strlen(env_node->name)) != 0)
		env_node = env_node->next;
	return (env_node);
}

static t_lexer_node	**find_envar_node(t_lexer_node **first_node)
{
	t_lexer_node	**current_node;

	current_node = &(*first_node);
	while (*(*current_node)->word != '$')
		*current_node = (*current_node)->next;
	return (current_node);
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
	write(1, "ok\n", 3);
	*current_string = concat_chain_to_string(first_node);
	if (!*current_string)
		return (ERROR);
	return (SUCCESS); 
}

int	expand_and_add_to_chain(t_lexer_node **envar_node, t_env_node *envar)
{
	char			**splited_envar;
	t_lexer_node	*subchain;

	splited_envar = ft_split(envar->value, ' ');
	write(1, "ok\n", 3);
	if (!splited_envar)
		return (ERROR);
	subchain = (t_lexer_node *)make_chain_from_array(splited_envar, create_lexer_node);
	write(1, "ok\n", 3);
	if (!subchain)
		return (ERROR);
	include_subchain_at((t_node **)envar_node, (t_node *)subchain);
	write(1, "ok\n", 3);
	return (SUCCESS);	
}
