/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:24:27 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/09 14:58:24 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static int	wait_for_current_pipeline(void);
static int	fork_and_exec(t_exec_node *current_command, \
							char **argv, char **envp, int pipefd[2]);
static char	**make_argument_array(t_exec_node *current_command);
static pid_t	manage_current_command_exec(t_exec_node *current_command);

/*		EXEC MANAGER		*/
int	exec_process_manager(void)
{
	int			pipeline_status;
	pid_t		fork_pid;
	t_exec_node	*current_command;

	if (exec_every_heredoc_of_pipeline(g_glo.execution_chain) != SUCCESS)
		return (ERROR);
	current_command = (t_exec_node *)create_exec_node(NULL);
	current_command->next = g_glo.execution_chain;
	while (current_command->next != NULL)
	{
		current_command = current_command->next;
		if (io_environment_manager(current_command) == ERROR)
			continue ;
		if (current_command->command_path == NULL)
			continue ;
		fork_pid = manage_current_command_exec(current_command);
		if (fork_pid == ERROR)
			return (ERROR);
		current_command->process_id = fork_pid;
	}
	pipeline_status = wait_for_current_pipeline();
	return (pipeline_status);
}

static pid_t	manage_current_command_exec(t_exec_node *current_command)
{
	int			fork_pid;
	char		**argv;
	char		**envp;
	t_node		*env_chain;
	static int	pipefd[2];

	pipefd[0] = NOT_SET;
	pipefd[1] = NOT_SET;
	env_chain = (t_node *)g_glo.env;
	argv = make_argument_array(current_command);
	envp = make_array_from_chain(env_chain, get_env_node_value);
	if (!argv || !envp)
		return (ERROR);
	if (current_command->next != NULL)
		if (pipe(pipefd) != SUCCESS)
			return (ERROR);
	fork_pid = fork_and_exec(current_command, argv, envp, pipefd);
	return (fork_pid);
}

static int	fork_and_exec(t_exec_node *current_command, \
							char **argv, char **envp, int pipefd[2])
{
	int		io_env_input;
	int		io_env_output;
	char	*command_path;
	pid_t	forked_pid;

	io_env_input = current_command->io_env.input;
	io_env_output = current_command->io_env.output;
	command_path = current_command->command_path;
	if (is_command_a_path(command_path) == 0)
		current_command->command_path = pathfinder_process(command_path);
	forked_pid = fork();
	if (forked_pid == 0)
	{
		if (manage_output_piping(pipefd, io_env_output) == SUCCESS)
			execve(current_command->command_path, argv, envp);
		exit(1);	
	}
	if (manage_input_piping(pipefd, io_env_input) != SUCCESS)
		return (ERROR);
	return (forked_pid);
}

static int	wait_for_current_pipeline(void)
{
	int			return_status;
	int			wait_ret_value;
	pid_t		pid_to_wait_for;
	t_exec_node	*current_node;

	wait_ret_value = SUCCESS;
	current_node = g_glo.execution_chain;
	while (current_node)
	{
		pid_to_wait_for = current_node->process_id;
		if (pid_to_wait_for != NOT_SET)
			wait_ret_value = waitpid(pid_to_wait_for, &return_status, 0);
		if (wait_ret_value == ERROR)
			return (ERROR);
		current_node = current_node->next;
	}
	return (return_status);
}

static char	**make_argument_array(t_exec_node *current_command)
{
	char			**ret_array;
	char			*command_path;
	t_lexer_node	*arg_chain;

	command_path = current_command->command_path;
	arg_chain = (t_lexer_node *)create_lexer_node(command_path);
	if (arg_chain == NULL)
		return (NULL);
	arg_chain->next = current_command->arg_chain;
	ret_array = make_array_from_chain((t_node *)arg_chain, \
										get_lexer_node_value);
	return (ret_array);
}