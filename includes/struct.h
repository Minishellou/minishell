/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:54:36 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 11:17:05 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define PIPE '|';
# define LESS '<';
# define GREAT '>';
# define LESSER '<' * 2;
# define GREATER  '>' * 2;

/*		GLOBAL STRUCT			*/
typedef struct s_global
{
	int						standard_input;
	int						standard_output;
	struct s_env_node		*env;
	struct s_garbage_node	*garbage_ctr;
	struct s_redirection	*redirection_table;
	struct s_lexer_node		*lexer_output_chain;
	struct s_exec_node		*execution_chain;
}				t_global;

/*		ENVIRONMENT CHAIN		*/
typedef struct s_env_node
{
	struct s_env_node	*next;
	char				*name;
	char				*value;
}				t_env_node;

/*		LEXER AND TOKENS		*/
typedef struct s_lexer_node
{
	struct s_lexer_node	*next;
	char				*word;
	char				*token;
}				t_lexer_node;

/*		EXECUTION CHAIN			*/
typedef struct s_exec_node
{
	struct s_exec_node	*next;
	char				*command_path;
	struct s_arg_node	*command_args;
}				t_exec_node;

typedef struct s_arg_node
{
	struct s_arg_node	*next;
	char				*word;
}				t_arg_node;

/*		REDIRECTION CHAIN		*/
enum	e_redirection_type
{
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND
};

typedef int	t_redirection_type;

typedef struct s_redirection
{
	struct s_redirection	*next;
	char					*argument;
	t_redirection_type		type;
}				t_redirection;

/*		QUOTE CONTEXT			*/
enum e_quote_context
{
	QUOTED,
	UNQUOTED
};

typedef int	t_quote_context;

/*		IO ENVIRONMENT			*/
typedef struct s_io_environment
{
	int	input_fd;
	int	output_fd;
}				t_io_env;

/*		NODE INTERFACE			*/
typedef struct s_node
{
	struct s_node	*next;
	char			*word;
	char			*var;
}				t_node;

typedef t_node	*t_node_creator(char *);
//	The function should allocate new_node to the right node type
//						set a member of new_node to its argument
//						set new_node->next to NULL
//						return the new_node casted as (t_node *)

/*		GARBAGE COLLECTOR		*/
typedef struct s_garbage_node
{
	void					*addr;
	struct s_garbage_node	*next;
}				t_garbage_node;

#endif