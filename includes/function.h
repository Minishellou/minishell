/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 06:07:20 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "./define.h"
# include "./struct.h"

/* INIT */
void			token_state_init(t_token_state *state);

/*		GLOBAL STRUCTURE		*/
int				init_global(char **envp);

/*		NODE & UTILS			*/
//	Create Node
t_node			*create_env_node(char *var);
t_node			*create_exec_node(char *word);
t_node			*create_lexer_node(char *word);
t_node			*create_redirection(char *argument);
//	Get node value
char			*get_env_node_value(t_node *node);
char			*get_lexer_node_value(t_node *node);
//	Utils
t_node			*make_chain_from_array(char **array, \
								t_node_creator create_node);
char			**make_array_from_chain(t_node *chain, \
								t_node_getter get_node_value);
void			append_to_chain(t_node **node, t_node *new_node);
t_node			*last_node(t_node *current_node);
int				get_chain_len(t_node *chain);
char			*concat_array_to_string(char **splited_string);

/*		ESCAPE & QUOTES UTILS	*/
//	Quotes
int				unquote_string(char **string);
int				is_quoted(char *string, int nb_of_quote);

/*		ENVAR & NODE UTILS		*/
//	Envar expansion
t_env_node		*get_envar(char *envar_name);
int				has_envar(char *string);

/*			REDIR MANAGEMENT			*/
//	Main function
int				io_environment_manager(t_exec_node *current_command);
//	Open functions
int				open_file_to_read(char *file_path);
int				open_file_to_trunc(char *file_path);
int				open_file_to_append(char *file_path);
//			HEREDOC
//	Main function
int				manage_heredoc(t_redirection *heredoc_node);
//	Execution
int				exec_every_heredoc_of_pipeline(t_exec_node *current_node);
//	Misc
int				process_limit_string(char **limit_string, int *quote_context);
void			write_to_file(int file_fd, char *string_to_write);

/*			EXEC PROCESS 				*/
//	Main function
int				exec_process_manager(void);
//			PATHFINDER
//	Main function
char			*pathfinder_process(char *command);
//	Conditional
int				is_command_a_path(char *command);
/*			IO MANAGEMENT				*/
//	Create pipe
int				create_pipe(t_exec_node *current_node);
//	Close pipe
void			close_pipe(void);
void			close_pipe_input(void);
void			close_pipe_output(void);
//	Manage redirection
void			manage_child_output_redirection(void);
void			manage_parent_input_redirection(void);
//	Manage unused fd
void			close_input_in_child(void);
void			close_output_in_parent(void);
//	Redirect std_IO
void			redirect_process_input(void);
void			redirect_process_output(void);
//	Restore std_IO
int				restore_standard_input(void);
int				restore_standard_output(void);
//	Misc
int				redirect_fd(int fd, int stdfd);

/*		BUILD INS		*/
//	cd
int				cd(int arg_number, t_lexer_node *arg_chain);
//	echo
void			echo(t_lexer_node *arg_chain);
//	env
int				env(void);
//	exit
void			exit_builtins(int arg_nb, t_lexer_node *arg_chain);
//	pwd
void			pwd(void);
//	export
int				export(int arg_number, t_lexer_node *arg_list);
//	unset
int				unset(t_lexer_node *arg_chain);

/*		GARBAGE COLLECTOR		*/
t_garbage_node	*new_grb_node(void *addr);
void			lst_addback(t_garbage_node *new_node);
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
void			printf_redir_chain(t_redirection *node);
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
t_redirection	*parse_redirection(t_exec_node *node, \
									t_lexer_node *output_chain);
t_exec_node		*command_output_context(t_exec_node *execute_chain, \
									t_lexer_node **lexer_output);
t_exec_node		*redirection_output_context(t_exec_node *execute_chain, \
										t_lexer_node **lexer_output);
t_exec_node		*command_process_loop(t_exec_node *execute_chain, \
									t_lexer_node **lexer_ouput);
t_exec_node		*redir_process_loop(t_exec_node *execute_chain, \
								t_lexer_node **lexer_output);
t_lexer_node	*add_argument(t_exec_node *node, char *word);
t_exec_node		*add_process(t_lexer_node **output_chain, t_exec_node *node);
t_redirection	*create_parse_redirection(t_lexer_node *output_chain);
void			printf_execute_chain(t_exec_node *node);
t_exec_node		*composer(void);
t_exec_node		*composer_process(t_lexer_node **lexer_output_chain);
char			*concat_chain_to_string(t_lexer_node *first_node);
char			*expand_envar_in_string(char *word);
int				positive(char **str);
int				unquoted_lexer_output_chain(void);
int				quote_positive(char **str, char c);
int				reset_single_quote_content_to_pst(void);
int				reset_double_quote_content_to_pst(void);
int				check_and_add_var(char *env_node, t_lexer_node **node, int *i);
t_lexer_node	*add_env_list(char *word, t_lexer_node *node);
int				check_and_get_envar(t_lexer_node **node, \
						t_env_node **current_var);
t_lexer_node	*envar_expansion(void);
t_lexer_node	*lexer_envar(char *env_node);
void			test(char *str);
#endif