/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:24:27 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/14 15:55:38 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_every_heredoc_of_pipeline(t_exec_node *current_node);
static int	fork_and_exec(t_exec_node *current_command);

/*		EXEC MANAGER		*/
int	exec_process_manager(void)
{
	int			fork_pid;
	int			pipe_in;
	int			pipeline_status;
	t_exec_node	*current_command;

	if (exec_every_heredoc_of_pipeline(g_glo.execution_chain) != SUCCESS)
		return (ERROR);
	current_command = g_glo.execution_chain;
	while (current_command != NULL)
	{
		if (io_environment_manager(current_command) == ERROR)
			perror("redirection:");
		else if (current_command->command_path != NULL)
		{	
			pipe_in = piping_manager(current_command->io_env, pipe_in);
			fork_pid = fork_and_exec(current_command);
		}
		current_command = current_command->next;
	}
	reset_standard_io();
	waitpid(fork_pid, &pipeline_status, 0);
	return (pipeline_status);
}

static int	exec_every_heredoc_of_pipeline(t_exec_node *current_node)
{
	t_redirection	*current_redir_chain;

	while (current_node != NULL)
	{
		current_redir_chain = current_node->redir_chain;
		while (current_redir_chain != NULL)
		{
			if (current_redir_chain->type == HEREDOC)
				if (manage_heredoc(current_redir_chain) != SUCCESS)
					return (ERROR);
			current_redir_chain = current_redir_chain->next;
		}
		current_node = current_node->next;
	}
	return (SUCCESS);
}

static int	fork_and_exec(t_exec_node *current_command)
{
	pid_t	forked_pid;
	t_node	*arg_chain;
	t_node	*env_chain;
	char	**envp;
	char	**argv;

	env_chain = (t_node *)g_glo.env;
	arg_chain = (t_node *)current_command->arg_chain;
	envp = make_array_from_chain(env_chain, get_env_node_value);
	argv = make_array_from_chain(arg_chain, get_lexer_node_value);
	forked_pid = fork();
	if (forked_pid == 0)
	{
		execve(current_command->command_path, argv, envp);
		return (ERROR);
	}
	return (forked_pid);
}