/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:39:07 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/09 12:55:37 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	open_input_redir(char *file_path, t_io_env *to_fill);
static void	open_output_redir(char *file_path, t_io_env *to_fill);
static void	open_append_redir(char *file_path, t_io_env *to_fill);

int	io_environment_manager(t_exec_node *current_command)
{
	int			input_fd;
	int			output_fd;
	t_io_env	current_io_env;

	input_fd = find_last_input_redir(g_glo.redirection_table);
	output_fd = find_last_output_redir(g_glo.redirection_table);
	if (input_fd == NOT_SET)
		input_fd = dup(g_glo.standard_input);
	if (output_fd == NOT_SET)
		output_fd = dup(g_glo.standard_output);
	current_io_env.input_fd = input_fd;
	current_io_env.output_fd = output_fd;
	return (current_io_env);
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
