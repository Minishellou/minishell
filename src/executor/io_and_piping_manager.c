/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_and_piping_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:33:17 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/08 12:38:26 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*		LOCAL IO MANAGER		*/
// int	piping_manager(t_io_env io_env, int pipe_in)
// {
// 	int	current_input_fd;
// 	int	current_output_fd;
// 	int	from_current_to_next[2];

// 	current_input_fd = io_env.input;
// 	current_output_fd = io_env.output;
// 	if (pipe_in == NOT_SET)
// 		pipe_in = dup(g_glo.standard_input);
// 	if (pipe(from_current_to_next) != SUCCESS)
// 		return (ERROR);
// 	if (current_input_fd == NOT_SET)
// 		current_input_fd = pipe_in;
// 	if (current_output_fd == NOT_SET)
// 		current_output_fd = from_current_to_next[1];
// 	if (redir_manager(current_input_fd, current_output_fd) != SUCCESS)
// 		return (ERROR);
// 	return (from_current_to_next[0]);
// }

int	reset_standard_io(void)
{
	if (dup2(g_glo.standard_input, 0) < 0)
		return (ERROR);
	if (dup2(g_glo.standard_output, 1) < 0)
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
