/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/16 11:23:35 by mcorso           ###   ########.fr       */
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
//	Escape char
int			delete_escaped_char(char **string);
void		mask_escaped_char(char **string);
void		restore_escaped_char(char **string);

/*		FILE & UTILS			*/
int			open_tmp_file(void);
int			open_file_to_read(char *file_path);
int			open_file_to_trunc(char *file_path);
int			open_file_to_append(char *file_path);
void		write_to_file(int file_fd, char *string_to_write);

/*		IO ENV & UTILS			*/
//	Manager
t_io_env	io_environment_manager(void);
//	Finders
int			find_last_output_redir(t_redirection *redirection);
int			find_last_input_redir(t_redirection *redirection);

/*		HEREDOC & UTILS			*/
//	Heredoc process
int			heredoc_process(char *limit_string);
//	Limit string
int			manage_limit_string(char **limit_string, int *quote_context);


/*		GARBAGE COLLECTOR		*/
//	Collect garbage
void				*ft_malloc(int len);
//	Throw garbage
void				ft_free(void);

#endif