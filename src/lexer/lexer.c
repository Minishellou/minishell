/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/01 19:46:37 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	make_chain_of_words(char *command)
{
	char	**words;
	t_node	*output_chain;
	
	words = ft_split(command, ' ');
	if (!words)
		return (1);
	output_chain = make_chain_from_array(words, create_lexer_node);
	g_glo.lexer_output_chain = (t_lexer_node *)output_chain;
	return (0);
}

int	lexer(char *command)
{
	if (make_chain_of_words(command) != 0)
		return (1);
	//	expand_envar();
	//	tokenize();
	return (0);
}
