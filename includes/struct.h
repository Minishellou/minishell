/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:54:36 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/31 12:30:01 by mcorso           ###   ########.fr       */
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

/*		LEXER AND TOKENS		*/
typedef struct s_lexer_node
{
	char				*token;
	char				*word;
	struct s_lexer_node	*next;
}				t_lexer_node;

/*		REDIRECTION CHAIN		*/
enum	e_redirection_type
{
	INPUT = 1,
	OUPUT = 2,
	APPEND = 3
};

typedef struct s_redirection
{
	char					*file_path;
	enum e_redirection_type	type;
}				t_redirection;


/*		EXECUTION CHAIN			*/
typedef struct s_exec_node
{
	char				*command_path;
	char				*command_args;
	struct s_exec_node	*next;
}				t_exec_node;

/*		ENVIRONMENT CHAIN		*/
typedef struct s_env_node
{
	char				*name;
	char				*value;
	struct s_env_node	*next;
}				t_env_node;

/*		GARBAGE COLLECTOR		*/
typedef struct s_garbage_node
{
	void					*addr;
	struct s_garbage_node	*next;
}				t_garbage_node;

#endif