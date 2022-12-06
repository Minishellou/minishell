/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/06 14:53:46 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "./struct.h"

/*		GLOBAL STRUCTURE		*/
int			init_global(char **envp);

/*		NODE & UTILS			*/
//	Env Node
int			fill_env_node(char *var, t_env_node *node);
//	Create Node
t_node		*create_env_node(char *var);
t_node		*create_lexer_node(char *word);
t_node		*create_redirection(char *argument);
//	Utils
t_node		*make_chain_from_array(char **array, \
										t_node_creator create_node);

/*		LEXER & UTILS			*/
//	Lexer
int			lexer(char *command);

/*		STRING CONVERT & UTILS	*/
char	*concat_array_to_string(char **splited_string);

/*		ESCAPE & QUOTES UTILS	*/
//	Quotes
int			unquote_string(char **string);
int			is_quoted(char *string, int nb_of_quote);

/*		FILE & UTILS			*/
int			open_file_to_read(char *file_path);
int			open_file_to_trunc(char *file_path);
int			open_file_to_append(char *file_path);
void		write_to_file(int file_fd, char *string_to_write);

/*		IO ENV & UTILS			*/
//	IO Env manager
int			io_environment_manager(t_exec_node *current_command);
//	Heredoc manager 
int			manage_heredoc(t_redirection *heredoc_node);
//	Limit string
int			process_limit_string(char **limit_string, int *quote_context);


/*		GARBAGE COLLECTOR		*/
//	Collect garbage
void				*ft_malloc(int len);
//	Throw garbage
void				ft_free(void);

#endif