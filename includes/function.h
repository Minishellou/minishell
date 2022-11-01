/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/01 12:34:08 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "./struct.h"


/*		GARBAGE COLLECTOR		*/
//	lexer
t_lexer_node	*new_lxr_lst(char *word);
t_lexer_node* ft_lxr_lstlast(t_lexer_node *lexer_node);
void    lst_lxr_addback(t_lexer_node *alst, t_lexer_node *new);
 void make_chain_from_array(char **str, t_lexer_node *lex);
 t_lexer_node lexer(char *str);
//	Collect garbage
void			*ft_malloc(int len);
void	init_global(void);
//	Throw garbage
void			ft_free(void);

#endif