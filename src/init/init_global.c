/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:01:49 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 15:56:20 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_state_init(t_token_state *state)
{
	state->less = false;
	state->great = false;
	state->lesser = false;
	state->greater = false;
	state->pipe = false;
}

int	init_global(char **envp)
{
	g_glo.standard_input = dup(0);
	g_glo.standard_output = dup(1);
	if (g_glo.standard_input < 0 || g_glo.standard_output < 0)
		return (ERROR);
	g_glo.garbage_ctr = NULL;
	g_glo.env = (t_env_node *)make_chain_from_array(envp, create_env_node);
	if (g_glo.env == NULL)
		return (ERROR);
	g_glo.redirection_table = NULL;
	g_glo.lexer_output_chain = NULL;
	g_glo.execution_chain = NULL;
	return (SUCCESS);
}
