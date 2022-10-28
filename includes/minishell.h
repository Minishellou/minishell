/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 16:48:22 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_token
{
	PIPE,
	LESS,
	GREAT,
	LESSER,
	GREATER,	
};

typedef struct s_lexer_node
{
	char				*word;
	char				*token;
	struct s_lexer_node	*next;
}				t_lexer_node;

typedef struct s_garbage_node
{
	void				*addr;
	struct S_garbage	*next;
}				t_garbage_node;
//t_garbage *garbage = NULL;
//GARBAGE COLLECTOR//
void			*ft_malloc(int len, t_garbage_node **genisis_block);
void			ft_free(t_garbage_node *genisis_block);
t_garbage_node	*new_lst(void *addr);
t_garbage_node	*ft_lstlast(t_garbage_node *genisis_block);
void			lst_addback(t_garbage_node **alst, t_garbage_node *new);

#endif