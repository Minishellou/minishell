/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/24 16:57:51 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void quote_rehestablish(char *str)
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

/*
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
		expand_envar();
		tokenize();
}
*/
int	lexer(char *input)
{
	char	**words;
	int		i;
	//t_node	*output_chain;
	
	if(quote_neon(&input) != SUCCESS)
		return (ERROR);
	if(parse_token(input) != SUCCESS)
		return (ERROR);
	words = ft_split_target(input, '|');
	while (words[i])
	{
		if (words[i][0] == '\0' && ft_strlen(words[i]) <= 2)
			return (ERROR);
		quote_neon(&words[i++]);
	}
	i = 0;
	while (words[i])
	{
		quote_rehestablish(words[i]);
		printf("%s\n", words[i++]);
	}
	return (SUCCESS);
}