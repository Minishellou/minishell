/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_and_piping_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:33:17 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/08 21:34:05 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	restore_standard_input(void);
static int	restore_standard_output(void);

/*		LOCAL IO MANAGER		*/
int	manage_output_piping(int pipefd[], int io_env_output)
{
	int	output_fd;
	int	pipe_write_end;
	int	ret_value;

	pipe_write_end = pipefd[1];
	output_fd = io_env_output;
	if (output_fd == NOT_SET)
		output_fd = pipe_write_end;
	if (output_fd == NOT_SET)
		ret_value = restore_standard_output();
	else
		ret_value = redirect_process_output(pipefd, output_fd);
	return (ret_value);
}

int	manage_input_piping(int pipefd[], int io_env_input)
{
	int	input_fd;
	int	pipe_read_end;
	int	ret_value;

	pipe_read_end = pipefd[0];
	input_fd = io_env_input;
	if (input_fd == NOT_SET)
		input_fd = pipe_read_end;
	if (input_fd == NOT_SET)
		ret_value = restore_standard_input();
	else
		ret_value = redirect_process_input(pipefd, input_fd);
	return (ret_value);
}

static int	restore_standard_input(void)
{
	int	ret_value;

	ret_value = dup2(g_glo.standard_input, 0);
	if (ret_value == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	restore_standard_output(void)
{
	int	ret_value;

	ret_value = dup2(g_glo.standard_output, 1);
	if (ret_value == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	redirect_fd(int fd, int stdfd)
{
	if (dup2(fd, stdfd) < 0)
		return (ERROR);
	if (close(fd) < 0)
		return (ERROR);
	return (SUCCESS);
}
