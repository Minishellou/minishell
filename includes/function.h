/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/10 13:12:19 by gkitoko          ###   ########.fr       */
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
t_lexer_node	*command_expression(t_lexer_node *cmd);
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
// manipulation
int neon(char **str);
int	quote_neon(char **str);
void unit_free(void *node);
void remove_node(t_node **current_node);
void	include_subchain_at(t_node **this_node, t_node *subchain);
t_node	*last_node(t_node *current_node);
void	lex_addback(t_lexer_node **node, t_lexer_node *new);
// state management 
int token_state(t_token_state state);
// print words list
void	print_word_list(t_lexer_node *node);
//redirection handler
void str_to_lexer_node(t_lexer_node **tmp);
// pipe handler
t_lexer_node	*process_spipe(char *input);
void	fill_lexer_output(t_lexer_node *command_list);
void 	add_command_to_lexer_output(t_lexer_node *first_node);
// token management
void switch_state(bool *old, bool *new);
int token_state_management(int *i, char **input, t_token_state *state);

#endif