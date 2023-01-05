/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/05 11:44:36 by gkitoko          ###   ########.fr       */
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
// Create exec node
t_node *create_exec_node(char *word);
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
int				process_lexer_output_chain(char *command);
int				catch_redir_error(void);
void			free_all(char **tab);

/* 		PARSING					*/
//	Token parser
int				catch_parsing_error(char *input);
int				illegal_token(t_lexer_node *node);
//  Check every char 
int				is_white_space(char c);
int				is_special_token(char c);
//	Manipulation
int				neon(char **str);
int				quote_neon(char **str);
void			unit_free(void *node);
void			remove_node(t_node **current_node);
void			append_to_chain(t_node **node, t_node *new_node);
void			include_subchain_at(t_node **this_node, t_node *subchain);
t_node			*last_node(t_node *current_node);
//	State management 
int				token_state(t_token_state state);
//	Print words list
void			print_word_list(t_lexer_node *node);
// Print redir list
void printf_redir_chain(t_redirection *node);
//	Redirection handler
int				empty_char(const char *str);
int				parse_redir_in_command_expression(t_lexer_node **tmp);
int				replace_and_track_next_node(t_lexer_node *to_replace, \
											t_lexer_node *subchain);
char			*copy_word_until_redirection(char *str);
t_lexer_node	*create_redir_node(char *str);
//	Pipe handler
t_lexer_node	*lexer_line_parsing_process(char *command_line);
//	Token management
int				token_state_management(int *i, char **input, \
										t_token_state *state);
void			switch_state(bool *old, bool *new_node);
//composer
t_redirection *parse_redirection(t_exec_node *node, t_lexer_node *output_chain);
t_exec_node *command_output_context(t_exec_node *execute_chain, t_lexer_node **lexer_output);
t_exec_node *redirection_output_context(t_exec_node *execute_chain, t_lexer_node **lexer_output);
t_lexer_node *add_argument(t_exec_node *node, char *word);
t_exec_node *add_process(t_lexer_node **output_chain, t_exec_node *node);
t_redirection *create_parse_redirection(t_lexer_node *output_chain);
void printf_execute_chain(t_exec_node *node);
t_exec_node *composer(void);
t_exec_node *composer_process(t_lexer_node **lexer_output_chain);
#endif