/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:24:27 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/08 15:45:56 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static int	manage_current_command_exec(t_exec_node *current_command);
static int	exec_every_heredoc_of_pipeline(t_exec_node *current_node);
static int	fork_and_exec(t_exec_node *current_command, \
							char **argv, char **envp, int pipefd[2]);
static char	**make_argument_array(t_exec_node *current_command);

/*		EXEC MANAGER		*/
int	exec_process_manager(void)
{
	int			fork_pid;
	int			pipeline_status;
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
	}
	waitpid(fork_pid, &pipeline_status, 0);
	if (restore_standard_input() != SUCCESS)
		return (ERROR);
	return (pipeline_status);
}

static int	manage_current_command_exec(t_exec_node *current_command)
{
	int			ret_value;
	char		**argv;
	char		**envp;
	t_node		*env_chain;
	static int	pipefd[2];

	env_chain = (t_node *)g_glo.env;
	argv = make_argument_array(current_command);
	envp = make_array_from_chain(env_chain, get_env_node_value);
	if (!argv || !envp)
		return (ERROR);
	if (current_command->next != NULL)
		if (pipe(pipefd) != SUCCESS)
			return (ERROR);
	ret_value = fork_and_exec(current_command, argv, envp, pipefd);
	return (ret_value);
}

static int	fork_and_exec(t_exec_node *current_command, \
							char **argv, char **envp, int pipefd[2])
{
	int		ret_value;
	char	*command_path;
	pid_t	forked_pid;

	command_path = current_command->command_path;
	if (is_command_a_path(command_path) == 0)
		current_command->command_path = pathfinder_process(command_path);
	forked_pid = fork();
	if (forked_pid == 0)
	{
		if (current_command->next != NULL)
			ret_value = redirect_process_output(pipefd);
		else
			ret_value = restore_standard_output();
		if (ret_value == SUCCESS)
			execve(current_command->command_path, argv, envp);
		perror(command_path);
		return (ERROR);
	}
	if (redirect_process_input(pipefd) != SUCCESS)
		return (ERROR);
	return (forked_pid);
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
