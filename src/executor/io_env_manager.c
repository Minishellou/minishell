/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:57:25 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/12 11:40:33 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_redirection_chain(t_redirection *redir_chain);
static int	open_input_redir(char *file_path);
static int	open_output_redir(char *file_path);
static int	open_append_redir(char *file_path);

int	io_environment_manager(t_exec_node *current_command)
{
	int				*in_file;
	int				*out_file;
	t_redirection	*current_redir_chain;

	in_file = &g_glo.current_in_file;
	out_file = &g_glo.current_out_file;
	current_redir_chain = current_command->redir_chain;
	handle_redirection_chain(current_redir_chain);
	if (*in_file != ERROR && *out_file != ERROR)
		return (SUCCESS);
	if (*in_file != ERROR)
		close(*in_file);
	if (*out_file != ERROR)
		close(*out_file);
	*in_file = NOT_SET;
	*out_file = NOT_SET;
	ft_putstr_fd(current_command->command_path, 2);
	return (perror(": in redirection argument"), ERROR);
}

static void	handle_redirection_chain(t_redirection *redir_chain)
{
	int				*in_file;
	int				*out_file;
	t_redirection	*current_redirection_node;

	in_file = &g_glo.current_in_file;
	out_file = &g_glo.current_out_file;
	*in_file = NOT_SET;
	*out_file = NOT_SET;
	current_redirection_node = redir_chain;
	while (current_redirection_node != NULL)
	{
		if (current_redirection_node->type == INPUT)
			*in_file = open_input_redir(current_redirection_node->argument);
		if (current_redirection_node->type == OUTPUT)
			*out_file = open_output_redir(current_redirection_node->argument);
		if (current_redirection_node->type == APPEND)
			*out_file = open_append_redir(current_redirection_node->argument);
		if (*in_file == ERROR || *out_file == ERROR)
			return ;
		current_redirection_node = current_redirection_node->next;
	}
	return ;
}

static int	open_input_redir(char *file_path)
{
	int	old_fd;

	old_fd = g_glo.current_in_file;
	if (old_fd != NOT_SET)
		close(old_fd);
	return (open_file_to_read(file_path));
}

static int	open_output_redir(char *file_path)
{
	int	old_fd;

	old_fd = g_glo.current_out_file;
	if (old_fd != NOT_SET)
		close(old_fd);
	return (open_file_to_trunc(file_path));
}

static int	open_append_redir(char *file_path)
{
	int	old_fd;

	old_fd = g_glo.current_out_file;
	if (old_fd != NOT_SET)
		close(old_fd);
	return (open_file_to_append(file_path));
}
