/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:57:25 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/06 11:40:43 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	open_input_redir(char *file_path, t_io_env *to_fill);
static void	open_output_redir(char *file_path, t_io_env *to_fill);
static void	open_append_redir(char *file_path, t_io_env *to_fill);

int	io_environment_manager(t_exec_node *current_command)
{
	t_io_env		ret_io_env;
	t_redirection	*current_redirection_node;

	ret_io_env.input = NOT_SET;
	ret_io_env.output = NOT_SET;
	if (current_command->next == NULL)
		ret_io_env.output = dup(g_glo.standard_output);
	current_redirection_node = current_command->redir_chain;
	while (current_redirection_node != NULL)
	{
		if (current_redirection_node->type == INPUT)
			open_input_redir(current_redirection_node->argument, &ret_io_env);
		if (current_redirection_node->type == OUTPUT)
			open_output_redir(current_redirection_node->argument, &ret_io_env);
		if (current_redirection_node->type == APPEND)
			open_append_redir(current_redirection_node->argument, &ret_io_env);
		if (ret_io_env.input == ERROR || ret_io_env.output == ERROR)
			return (ERROR);
		current_redirection_node = current_redirection_node->next;
	}
	current_command->io_env.input = ret_io_env.input;
	current_command->io_env.output = ret_io_env.output;
	return (SUCCESS);
}

static void	open_input_redir(char *file_path, t_io_env *to_fill)
{
	if (to_fill->input != NOT_SET)
		close(to_fill->input);
	to_fill->input = open_file_to_read(file_path);
}

static void	open_output_redir(char *file_path, t_io_env	*to_fill)
{
	if (to_fill->output != NOT_SET)
		close(to_fill->output);
	to_fill->output = open_file_to_trunc(file_path);
}

static void	open_append_redir(char *file_path, t_io_env	*to_fill)
{
	if (to_fill->output != NOT_SET)
		close(to_fill->output);
	to_fill->output = open_file_to_append(file_path);
}
