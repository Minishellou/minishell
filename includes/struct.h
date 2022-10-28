/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:54:36 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/28 16:54:24 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./minishell.h"

	/*		GLOBAL STRUCT			*/
	typedef struct	s_global
	{
		int						standard_input;
		int						standard_output;
		char					*gobal_environment;
		t_garbage_node			*garbage_collector_chain;
		struct s_redirection	redirection_table[2];
		struct s_lexer_node		*lexer_output_chain;
		struct s_exec_node		*execution_chain;
	};

	/*		REDIRECTION STRUCT		*/
	enum	redirection_type
	{
		INPUT,
		OUPUT,
		APPEND
	};

	typedef struct	s_redirection
	{
		char				*file_path;
		redirection_type	type;
	}				t_redirection;

	/*		EXECUTION CHAIN			*/
	typedef struct	s_exec_node
	{
		char				*command_path;
		char				*command_args;
		struct s_exec_node	*next;
	}				t_exec_node;

#endif