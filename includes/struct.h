/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:54:36 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/28 21:05:49 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H


/*		REDIRECTION STRUCT		*/
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

	/*		GLOBAL STRUCT			*/
typedef struct s_global
{
	int						standard_input;
	int						standard_output;
	char					*gobal_environment;
	struct s_garbage_node	*garbage_collector_chain;
	struct s_redirection	redirection_table[2];
	struct s_lexer_node		*lexer_output_chain;
	struct s_exec_node		*execution_chain;
}				t_global;

/*		LEXER AND TOKENS		*/
enum e_token
{
	PIPE,
	LESS,
	GREAT,
	LESSER,
	GREATER,	
};

typedef struct s_lexer_node
{
	char				*word;
	char				*token;
	struct s_lexer_node	*next;
}				t_lexer_node;

/*		EXECUTION CHAIN			*/
typedef struct s_exec_node
{
	char				*command_path;
	char				*command_args;
	struct s_exec_node	*next;
}				t_exec_node;

/*		GARBAGE COLLECTOR		*/
typedef struct s_garbage_node
{
	void					*addr;
	struct s_garbage_node	*next;
}				t_garbage_node;

#endif