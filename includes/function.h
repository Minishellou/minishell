/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/09 12:55:22 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "./struct.h"
# include "./define.h"

/* INIT */
void			token_state_init(t_token_state *state);

/*		GLOBAL STRUCTURE		*/
int			init_global(char **envp);

/*		T_NODE & UTILS			*/
//	Create Node
t_node		*create_env_node(char *var);
t_node		*create_lexer_node(char *word);
t_node		*create_redirection(char *argument);
//	Get node value
char		*get_env_node_value(t_node	*node);
char		*get_lexer_node_value(t_node *node);
//	Utils
void		include_subchain_at(t_node **this_node, t_node *subchain);
t_node		*last_node(t_node *current_node);
t_node		*make_chain_from_array(char **array, \
										t_node_creator create_node);
char		**make_array_from_chain(t_node *chain, \
										t_node_getter get_node_value);
void		append_to_chain(t_node **node, t_node *new_node);
t_node		*last_node(t_node *current_node);

/*		STRING CONVERT & UTILS	*/
char		*concat_array_to_string(char **splited_string);
char		*concat_chain_to_string(t_lexer_node *first_node);

/*		ESCAPE & QUOTES UTILS	*/
//	Quotes
int			unquote_string(char **string);
int			is_quoted(char *string, int nb_of_quote);

/*		ENVAR & NODE UTILS		*/
//	Envar expansion
t_env_node	*get_envar(char *envar_name);

/*		ENVAR & NODE UTILS		*/
//	Envar expansion
t_env_node	*get_envar(char *envar_name);
int			expand_and_add_to_string(char **current_string, t_env_node *envar);
int			expand_and_add_to_chain(t_lexer_node **envar_node, t_env_node *envar);
//	Expansion utils
int			has_envar(char *string);
//	env_node
int			fill_env_node(char *var, t_env_node *node);

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
int			exec_every_heredoc_of_pipeline(t_exec_node *current_node);
//	Limit string
int			process_limit_string(char **limit_string, int *quote_context);

/*		EXEC & PIPING */
//	PATHFinder
char		*pathfinder_process(char *command);
int			is_command_a_path(char *command);
//	Exec process
int			exec_process_manager(void);
//	Pipe
// int			piping_manager(t_io_env io_env, int pipe_in);
int			redirect_fd(int fd, int stdfd);
//	Cleaning
int			reset_standard_io(void);
//		INLINE
static inline int	redirect_process_input(int pipefd[])
{
	int	input_fd;

	input_fd = pipefd[0];
	close(pipefd[1]);
	if (redirect_fd(input_fd, 0) != SUCCESS)
		return (ERROR);
	close(input_fd);
	return (SUCCESS);
}	

static inline int	redirect_process_output(int pipefd[])
{
	int	output_fd;

	output_fd = pipefd[1];
	close(pipefd[0]);
	if (redirect_fd(output_fd, 1) != SUCCESS)
		return (ERROR);
	close(output_fd);
	return (SUCCESS);	
}

static inline int	restore_standard_input(int stdfd)
{
	int	ret_value;

	ret_value = dup2(stdfd, 0);
	if (ret_value == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static inline int	restore_standard_output(int stdfd)
{
	int	ret_value;

	ret_value = dup2(stdfd, 1);
	if (ret_value == ERROR)
		return (ERROR);
	return(SUCCESS);
}

/*		GARBAGE COLLECTOR		*/
//	Collect garbage
void		*ft_malloc(int len);
//	Throw garbage
void		ft_free(void);

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
t_exec_node *command_process_loop(t_exec_node *execute_chain, t_lexer_node **lexer_ouput);
t_exec_node *redir_process_loop(t_exec_node *execute_chain, t_lexer_node **lexer_output);
t_lexer_node *add_argument(t_exec_node *node, char *word);
t_exec_node *add_process(t_lexer_node **output_chain, t_exec_node *node);
t_redirection *create_parse_redirection(t_lexer_node *output_chain);
void printf_execute_chain(t_exec_node *node);
t_exec_node *composer(void);
t_exec_node *composer_process(t_lexer_node **lexer_output_chain);
#endif