/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:24:27 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/05 15:58:18 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static int	fork_and_exec(t_exec_node *current_command, char *first_argument);
static int	manage_current_command_exec(t_exec_node *current_command);
static int	exec_every_heredoc_of_pipeline(t_exec_node *current_node);
static char	**make_argument_array(t_exec_node *current_command, \
								char *first_argument);

/*		EXEC MANAGER		*/
int	exec_process_manager(void)
{
	int			fork_pid;
	int			pipeline_status;
	t_exec_node	*current_command;

	if (exec_every_heredoc_of_pipeline(g_glo.execution_chain) != SUCCESS)
		return (ERROR);
	current_command = g_glo.execution_chain;
	while (current_command != NULL)
	{
		fork_pid = manage_current_command_exec(current_command);
		if (fork_pid == ERROR)
			return (ERROR);
		current_command = current_command->next;
	}
	reset_standard_io();
	waitpid(fork_pid, &pipeline_status, 0);
	return (pipeline_status);
}

static int	manage_current_command_exec(t_exec_node *current_command)
{
	int			ret_value;
	char		*command;
	char		*original_command_path;
	static int	pipe_in;

	command = current_command->command_path;
	if (io_environment_manager(current_command) == ERROR)
		return (SUCCESS);
	if (command == NULL)
		return (SUCCESS);
	original_command_path = current_command->command_path;
	if (is_command_a_path(command) == 0)
		current_command->command_path = pathfinder_process(command);
	pipe_in = piping_manager(current_command->io_env, pipe_in);
	ret_value = fork_and_exec(current_command, original_command_path);
	return (ret_value);
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

static int	fork_and_exec(t_exec_node *current_command, char *first_argument)
{
	pid_t	forked_pid;
	t_node	*env_chain;
	char	**envp;
	char	**argv;

	env_chain = (t_node *)g_glo.env;
	envp = make_array_from_chain(env_chain, get_env_node_value);
	argv = make_argument_array(current_command, first_argument);
	forked_pid = fork();
	if (forked_pid == 0)
	{
		execve(current_command->command_path, argv, envp);
		perror("execve:");
		return (ERROR);
	}
	return (forked_pid);
}

static char	**make_argument_array(t_exec_node *current_command, \
									char *first_argument)
{
	char			**ret_array;
	t_lexer_node	*arg_chain;

	arg_chain = (t_lexer_node *)create_lexer_node(first_argument);
	if (arg_chain == NULL)
		return (NULL);
	arg_chain->next = current_command->arg_chain;
	ret_array = make_array_from_chain((t_node *)arg_chain, \
										get_lexer_node_value);
	return (ret_array);
}
