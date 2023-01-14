/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:24:27 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/14 17:36:18 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		wait_for_current_pipeline(void);
static int		fork_and_exec(t_exec_node *current_command, \
							char **argv, \
							char **envp);
static char		**make_argument_array(t_exec_node *current_command);
static pid_t	manage_current_command_exec(t_exec_node *current_command);

/*		EXEC MANAGER		*/
int	exec_process_manager(void)
{
	int			pipeline_status;
	pid_t		fork_pid;
	t_exec_node	*current_command;

	if (exec_every_heredoc_of_pipeline(g_glo.execution_chain) != SUCCESS)
		return (ERROR);
	current_command = g_glo.execution_chain;
	while (current_command != NULL)
	{
		fork_pid = manage_current_command_exec(current_command);
		if (fork_pid == ERROR)
			return (ERROR);
		if (fork_pid != SUCCESS)
			current_command->process_id = fork_pid;
		current_command = current_command->next;
	}
	restore_standard_input();
	restore_standard_output();
	pipeline_status = wait_for_current_pipeline();
	return (pipeline_status);
}

static pid_t	manage_current_command_exec(t_exec_node *current_command)
{
	int		ret_status;
	char	**argv;
	char	**envp;
	t_node	*env_chain;

	ret_status = io_environment_manager(current_command);
	manage_parent_input_redirection();
	if (create_pipe(current_command) != SUCCESS)
		return (ERROR);
	if (ret_status == ERROR)
		return (close_pipe_output(), SUCCESS);
	if (current_command->command_path == NULL)
		return (SUCCESS);
	env_chain = (t_node *)g_glo.env;
	argv = make_argument_array(current_command);
	envp = make_array_from_chain(env_chain, get_env_node_value);
	if (!argv || !envp)
		return (ERROR);
	return (fork_and_exec(current_command, argv, envp));
}

static int	fork_and_exec(t_exec_node *current_command,
							char **argv,
							char **envp)
{
	char	*command_path;
	pid_t	forked_pid;

	command_path = current_command->command_path;
	forked_pid = fork();
	if (forked_pid == 0)
	{
		manage_child_output_redirection();
		close_input_in_child();
		if (is_command_a_path(command_path) == 1)
		{
			execve(command_path, argv, envp);
			ft_putstr_fd("minishell: ", 2);
			perror(command_path);
			exit(127);
		}
		command_path = pathfinder_process(command_path);
		execve(command_path, argv, envp);
		ft_putstr_fd(command_path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	close_output_in_parent();
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
