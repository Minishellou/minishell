/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:46:54 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/19 12:07:48 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*get_envar(char *envar_name)
{
	t_env_node	*env_node;

	env_node = g_glo.env;
	while (env_node && ft_strncmp(env_node->name, envar_name, ft_strlen(envar_name)) != 0)
		env_node = env_node->next;
	return (env_node);
}

int	expand_and_add_to_chain(t_lexer_node **envar_node, t_env_node envar)
{
	char			**splited_envar;
	t_lexer_node	*subchain;

	if (!envar)
		return (ERROR);
	splited_envar = ft_split(envar, ' ');
	if (!splited_envar)
		return (ERROR);
	subchain = (t_lexer_node *)make_chain_from_array(splited_envar, create_lexer_node);
	if (!subchain)
		return (ERROR)
	include_subchain_at((t_node *)envar_node, (t_node *)subchain);
	return (SUCCESS);	
}
