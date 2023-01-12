/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:01:33 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/12 11:43:17 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	create_pipe(t_exec_node *current_node)
{
	int	*pipe_buff;

	pipe_buff = &(*g_glo.pipe_buff);
	pipe_buff[0] = NOT_SET;
	pipe_buff[1] = NOT_SET;
	if (current_node->next == NULL)
		return (SUCCESS);
	if (pipe(pipe_buff) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	close_pipe(void)
{
	close_pipe_input();
	close_pipe_output();
}

void	close_pipe_input(void)
{
	int	*in_pipe_fd;

	in_pipe_fd = &g_glo.pipe_buff[0];
	if (*in_pipe_fd != NOT_SET)
		close(*in_pipe_fd);
	*in_pipe_fd = NOT_SET;
}

void	close_pipe_output(void)
{
	int	*out_pipe_fd;

	out_pipe_fd = &g_glo.pipe_buff[1];
	if (*out_pipe_fd != NOT_SET)
		close(*out_pipe_fd);
	*out_pipe_fd = NOT_SET;
}
