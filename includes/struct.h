/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:54:36 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/04 12:07:14 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define PIPE '|'
# define LESS '<' 
# define GREAT '>'

#include <stdbool.h>
/*		GLOBAL STRUCT			*/
typedef struct s_global
{
	int						standard_input;
	int						standard_output;
	struct s_env_node		*env;
	struct s_garbage_node	*garbage_ctr;
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
	int 				token;
}				t_lexer_node;

/*		IO ENVIRONMENT			*/
typedef struct s_io_environment
{
	int	input;
	int	output;
}				t_io_env;

/*		EXECUTION CHAIN			*/
typedef struct s_exec_node
{
	struct s_exec_node		*next;
	char					*command_path;
	t_lexer_node			*arg_chain;
	struct s_redirection	*redir_chain;
	t_io_env				io_env;
}				t_exec_node;

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

/*		NODE INTERFACE			*/
typedef struct s_node
{
	struct s_node	*next;
}				t_node;

/* HANDLING TOKEN STATE FOR PARSING */
typedef struct s_token_state{
	bool less;
	bool great;
	bool lesser;
	bool greater;
	bool pipe;
}		t_token_state;

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