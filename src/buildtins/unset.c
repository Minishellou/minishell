/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:21:49 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 05:31:52 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
void	pop_env(char *envar_name)
{
	t_env_node	*tmp;
	t_env_node	*current_node;

	current_node = g_glo.env;
	tmp = current_node;
	while (current_node)
	{
		if (ft_strcmp(current_node->name, envar_name) == SUCCESS)
			break ;
		tmp = current_node;
		current_node = current_node->next;
	}
	if (!current_node)
		return ;
	tmp->next = current_node->next;
	return ;
}

int	unset(t_lexer_node *arg_chain)
{
	char			*current_var_name;

	if (!arg_chain)
		return (SUCCESS);
	while (arg_chain)
	{
		current_var_name = arg_chain->word;
		if (!current_var_name)
			return (ERROR);
		pop_env(current_var_name);
		arg_chain = arg_chain->next;
	}
	return (SUCCESS);
}
