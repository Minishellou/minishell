/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/15 15:46:42 by gkitoko          ###   ########.fr       */
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
	char **words;

	if ()
	//	expand_envar();
	//	tokenize();
	return (0);
}

**/