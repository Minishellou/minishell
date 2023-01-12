/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_piping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:57:35 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/12 11:38:13 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_child_output_redirection(void)
{
	int	*out_pipe_fd;
	int	*out_file_fd;

	out_pipe_fd = &g_glo.pipe_buff[1];
	out_file_fd = &g_glo.current_out_file;
	if (*out_pipe_fd == NOT_SET && *out_file_fd == NOT_SET)
		restore_standard_output();
	else
		redirect_process_output();
	*out_pipe_fd = NOT_SET;
	*out_file_fd = NOT_SET;
}

void	close_input_in_child(void)
{
	int	*in_pipe_fd;
	int	*in_file_fd;

	in_pipe_fd = &g_glo.pipe_buff[0];
	in_file_fd = &g_glo.current_in_file;
	if (*in_pipe_fd != NOT_SET)
		close(*in_pipe_fd);
	if (*in_file_fd != NOT_SET)
		close(*in_file_fd);
	*in_pipe_fd = NOT_SET;
	*in_file_fd = NOT_SET;
}

void	manage_parent_input_redirection(void)
{
	int	*in_pipe_fd;
	int	*in_file_fd;

	in_pipe_fd = &g_glo.pipe_buff[0];
	in_file_fd = &g_glo.current_in_file;
	if (*in_pipe_fd == NOT_SET && *in_file_fd == NOT_SET)
		restore_standard_input();
	else
		redirect_process_input();
	*in_pipe_fd = NOT_SET;
	*in_file_fd = NOT_SET;
}

void	close_output_in_parent(void)
{
	int	*out_pipe_fd;
	int	*out_file_fd;

	out_pipe_fd = &g_glo.pipe_buff[1];
	out_file_fd = &g_glo.current_out_file;
	if (*out_pipe_fd != NOT_SET)
		close(*out_pipe_fd);
	if (*out_file_fd != NOT_SET)
		close(*out_file_fd);
	*out_pipe_fd = NOT_SET;
	*out_file_fd = NOT_SET;
}
