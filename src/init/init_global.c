/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:01:49 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/01 19:35:41 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_global(char **envp)
{
	g_glo.standard_input = dup(0);
	g_glo.standard_output = dup(1);
	g_glo.env = (t_env_node *)make_chain_from_array(envp, create_env_node);
	g_glo.garbage_ctr = NULL;
	g_glo.redirection_table = NULL;
	g_glo.lexer_output_chain = NULL;
	g_glo.execution_chain = NULL;
}