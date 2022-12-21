/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:22:28 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/21 13:23:39 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	illegal_token(t_lexer_node *node)
{
	if (node->token == GREAT && node->next)
		if (node->next->token != 10)
			return (ERROR);
	if (node->token == GREATER && node->next)
		if (node->next->token != 10)
			return (ERROR);
	if (node->token == LESS && node->next)
		if (node->next->token != 10)
			return (ERROR);
	if (node->token == LESSER && node->next)
		if (node->next->token != 10)
			return (ERROR);
	if (node->token == PIPE && node->next)
		if (node->next->token != 10)
			return (ERROR);
	return (SUCCESS);
}

int	catch_redir_error(void)
{
	t_lexer_node	*tmp;

	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		if (illegal_token(tmp) != SUCCESS)
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
