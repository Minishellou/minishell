/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/01 18:28:42 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../includes/minishell.h"

 void make_chain_from_array(char **str, t_lexer_node *lex)
{
	int i;

	i = 1;
	lex = new_lxr_lst(str[i]);
	i++;
	while (str[i])
		lst_lxr_addback(lex, new_lxr_lst(str[++i]));
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

t_lexer_node lexer(char *str)
{
	char **split;
	t_lexer_node *lex;

	lex = NULL;	
	split = ft_split(str, ' ');
	make_chain_from_array(split, lex);
	return (*lex);
}
*/