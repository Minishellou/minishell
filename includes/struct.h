/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:54:36 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 17:15:41 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define PIPE '|'; x
# define LESS '<'; 
# define GREAT '>';
# define LESSER '<' * 2; x
# define GREATER  '>' * 2; x

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
	char				*var;
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
	char				*command_path;
	char				*command_args;
	struct s_exec_node	*next;
}				t_exec_node;

/*		REDIRECTION CHAIN		*/
enum	e_redirection_type
{
	INPUT,
	OUPUT,
	APPEND
};

typedef struct s_redirection
{
	char					*file_path;
	enum e_redirection_type	type;
}				t_redirection;

/*		NODE INTERFACE			*/
typedef struct s_node
{
	struct s_node	*next;
	char			*word;
	char			*var;
}				t_node;

//HANDLING TOKEN STATE FOR PARSING
typedef struct s_token_state{
	bool less = false; 
	bool great = false;
	bool lesser = false;
	bool greater = false;
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