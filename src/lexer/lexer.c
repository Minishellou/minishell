/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/16 17:14:34 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void quote_unscaped_establish(char *str)
{
	int i;

	if (!str)
		return ; 
	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

static int	make_chain_of_words(char *input)
{
	char			**words;
	int				i;
	t_lexer_node	*output_chain;

	
	if(!quote_space_to_neg(&input))
		return (EXIT_FAILURE);
	words = ft_split_target(input, '|');
	if (!words)
		return (0);
	i = 0;
	output_chain = (t_lexer_node *)make_chain_from_array(words, create_lexer_node);
	//	expand_envar();
	//	tokenize();
}

int	lexer(char *input)
{
	char	**words;
	int		i;
	t_node	*output_chain;


	if(!quote_space_to_neg(&input))
		return (0);
	words = ft_split(input, ' ');
	while ()	
	if (!words)
		return (0);
	output_chain =  make_chain_from_array(words, )
	//	expand_envar();
	//	tokenize();
	return (1);
}
