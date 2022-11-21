/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/21 15:35:42 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "./struct.h"

/* INIT */
void	token_state_init(t_token_state *state);

/*		GLOBAL STRUCTURE		*/
int				init_global(char **envp);

/*		NODE & UTILS			*/
//	Env Node
t_node			*create_env_node(char *var);
int				fill_env_node(char *var, t_env_node *node);
//	Create Node
t_node			*create_lexer_node(char *word);
//	Utils
t_node			*make_chain_from_array(char **array, \
										t_node_creator create_node);

/*		LEXER & UTILS			*/
//	Lexer
int				lexer(char *command);
/* PARSING */
int parse_token(char *input);
/*		GARBAGE COLLECTOR		*/
//	Collect garbage
void			*ft_malloc(int len);
//	Throw garbage
void			ft_free(void);
//  check every char 
int				is_white_space(char c);
int				is_special_token(char c);

// state management 
int token_state(t_token_state state);
void switch_state(bool *old, bool *new);
int token_state_management(int *i, char **input, t_token_state *state);

#endif