/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:27:42 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 16:37:50 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer_node	*new_lxr_lst(char *word, t_garbage_node **genisis_block)
{
	t_lexer_node* lexer_node = ft_malloc(sizeof(t_lexer_node), genisis_block);
	
    if (!lexer_node)
        return NULL;
    lexer_node->word = word;
    lexer_node->next = NULL;
    return (lexer_node);
}

t_lexer_node* ft_lxr_lstlast(t_lexer_node *lexer_node)
{
    while (lexer_node->next)
    {
        lexer_node = lexer_node->next;
    }
    return (lexer_node);
}

void    lst_lxr_addback(t_lexer_node **alst, t_lexer_node *new)
{
    if (!new)
        return ;
    else if (*alst)
        ft_lstlast(*alst)->next = new;
    else
        *alst = new;
}