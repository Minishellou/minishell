/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:33:17 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/14 12:57:30 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*		LOCAL IO MANAGER		*/
void	redirect_process_input(void)
{
	int	in_pipe_fd;
	int	in_file_fd;

	in_pipe_fd = g_glo.pipe_buff[0];
	in_file_fd = g_glo.current_in_file;
	if (in_pipe_fd != NOT_SET)
		redirect_fd(in_pipe_fd, 0);
	if (in_file_fd != NOT_SET)
		redirect_fd(in_file_fd, 0);
	return ;
}

void	redirect_process_output(void)
{
	int	out_pipe_fd;
	int	out_file_fd;

	out_pipe_fd = g_glo.pipe_buff[1];
	out_file_fd = g_glo.current_out_file;
	if (out_pipe_fd != NOT_SET)
		redirect_fd(out_pipe_fd, 1);
	if (out_file_fd != NOT_SET)
		redirect_fd(out_file_fd, 1);
	return ;
}

int	restore_standard_input(void)
{
	int	ret_value;

	ret_value = dup2(g_glo.standard_input, 0);
	if (ret_value == ERROR)
		return (perror("restore_stdin"), ERROR);
	return (SUCCESS);
}

int	restore_standard_output(void)
{
	int	ret_value;

	ret_value = dup2(g_glo.standard_output, 1);
	if (ret_value == ERROR)
		return (perror("restore_stdout"), ERROR);
	return (SUCCESS);
}

int	redirect_fd(int fd, int stdfd)
{
	int	ret_value;

	ret_value = dup2(fd, stdfd);
	if (ret_value < 0)
		return (write(2, "dup2: ", 7), ERROR);
	ret_value = close(fd);
	if (ret_value < 0)
		return (write(2, "close: ", 8), ERROR);
	return (SUCCESS);
}
