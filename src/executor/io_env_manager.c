/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:39:07 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 11:47:41 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_io_env	io_environment_manager(void)
{
	int					input_fd;
	int					output_fd;
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

int	find_last_input_redir(t_redirection *redirection)
{
	int			ret;
	static int	fd = NOT_SET;

	if (redirection == NULL)
		return (fd);
	if (redirection->type > HEREDOC)
		return (find_last_input_redir(redirection->next));
	if (fd != NOT_SET)
		close(fd);
	if (redirection->type == INPUT)
		fd = open_file_to_read(redirection->argument);
	if (redirection->type == HEREDOC)
		fd = heredoc_process(redirection->argument);
	if (fd == ERROR)
		return (ERROR);
	ret = find_last_input_redir(redirection->next);
	return (ret);
}

int	find_last_output_redir(t_redirection *redirection)
{	
	int			ret;
	static int	fd = NOT_SET;

	if (redirection == NULL)
		return (fd);
	if (redirection->type < OUTPUT)
		return (find_last_output_redir(redirection->next));
	if (fd != NOT_SET)
		close(fd);
	if (redirection->type == OUTPUT)
		fd = open_file_to_trunc(redirection->argument);
	if (redirection->type == APPEND)
		fd = open_file_to_append(redirection->argument);
	if (fd < 0)
		return (ERROR);
	ret = find_last_output_redir(redirection->next);
	return (ret);
}
