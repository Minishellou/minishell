/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 15:54:32 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "./struct.h"

/* INIT */
void			token_state_init(t_token_state *state);

/*		GLOBAL STRUCTURE		*/
int				init_global(char **envp);

/*		NODE & UTILS			*/
//	Env Node
int				fill_env_node(char *var, t_env_node *node);
t_node			*create_env_node(char *var);
//	Create Node
t_node			*create_lexer_node(char *word);
//	Utils
t_node			*make_chain_from_array(char **array, \
										t_node_creator create_node);

/*		GARBAGE COLLECTOR		*/
//	Collect garbage
void			*ft_malloc(int len);
//	Throw garbage
void			ft_free(void);

/*		LEXER & UTILS			*/
//	Lexer
int				chain_parse(void);
int				lexer(char *command);
void			free_all(char **tab);
t_lexer_node	*command_expression(t_lexer_node *cmd);

/* 		PARSING					*/
//	Token parser
int				parse_token(char *input);
int				illegal_token(t_lexer_node *node);
//  Check every char 
int				is_white_space(char c);
int				is_special_token(char c);
//	Manipulation
int				neon(char **str);
int				quote_neon(char **str);
void			unit_free(void *node);
void			remove_node(t_node **current_node);
void			lex_addback(t_lexer_node **node, t_lexer_node *new_node);
void			include_subchain_at(t_node **this_node, t_node *subchain);
t_node			*last_node(t_node *current_node);
//	State management 
int				token_state(t_token_state state);
//	Print words list
void			print_word_list(t_lexer_node *node);
//	Redirection handler
int				empty_char(const char *str);
void			str_to_lexer_node(t_lexer_node **tmp);
//	Pipe handler
void			fill_lexer_output(t_lexer_node *command_list);
void			add_command_to_lexer_output(t_lexer_node *first_node);
t_lexer_node	*process_spipe(char *input);
//	Token management
int				token_state_management(int *i, char **input, \
										t_token_state *state);
void			switch_state(bool *old, bool *new_node);

#endif