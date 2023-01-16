/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:24:27 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/16 12:22:00 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		wait_for_current_pipeline(void);
static void		fork_and_exec(t_exec_node *current_command, \
							char **argv, \
							char **envp);
static int		manage_current_command_exec(t_exec_node *current_command);
static int		get_signal_return_status(int return_status);


/*		EXEC MANAGER		*/
int	exec_process_manager(void)
{
	int			waitpid_status;
	int			pipeline_status;
	t_exec_node	*current_command;

	if (exec_every_heredoc_of_pipeline(g_glo.execution_chain) != SUCCESS)
		return (ERROR);
	ignore_sig();
	current_command = g_glo.execution_chain;
	while (current_command != NULL)
	{
		pipeline_status = manage_current_command_exec(current_command);
		if (pipeline_status == ERROR)
			return (ERROR);
		current_command->return_status = pipeline_status;
		current_command = current_command->next;
	}
	restore_standard_input();
	restore_standard_output();
	g_glo.ret_status = NOT_SET;
	waitpid_status = wait_for_current_pipeline();
	return (waitpid_status);
}

static int	manage_current_command_exec(t_exec_node *current_command)
{
	int		ret_status;
	char	**argv;
	char	**envp;

	argv = make_argument_array(current_command);
	envp = make_array_from_chain((t_node *)g_glo.env, get_env_node_value);
	if (!argv || !envp)
		return (ERROR);
	ret_status = io_environment_manager(current_command);
	manage_parent_input_redirection();
	if (create_pipe(current_command) != SUCCESS)
		return (ERROR);
	if (ret_status == ERROR)
		return (close_pipe_output(), 1);
	if (current_command->command_path == NULL)
		return (SUCCESS);
	if (current_command->next == NULL)
		if (is_a_builtin(current_command->command_path))
			return (exec_builtin(current_command));
	fork_and_exec(current_command, argv, envp);
	return (NOT_SET);
}

static void	fork_and_exec(t_exec_node *current_command, \
							char **argv, char **envp)
{
	char	*command_path;
	pid_t	forked_pid;

	command_path = current_command->command_path;
	forked_pid = fork();
	if (forked_pid == 0)
	{
		restore_sig();
		manage_child_output_redirection();
		close_input_in_child();
		if (is_a_builtin(command_path))
			exit(exec_builtin(current_command));
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
	current_command->process_id = forked_pid;
	close_output_in_parent();
}

static int	wait_for_current_pipeline(void)
{
	int			return_status;
	int			wait_ret_value;
	pid_t		pid_to_wait_for;
	t_exec_node	*current_node;

	return_status = 0;
	wait_ret_value = SUCCESS;
	current_node = g_glo.execution_chain;
	while (current_node)
	{
		pid_to_wait_for = current_node->process_id;
		if (pid_to_wait_for == NOT_SET)
		{
			current_node = current_node->next;
			continue ;
		}
		if (pid_to_wait_for != NOT_SET)
			wait_ret_value = waitpid(pid_to_wait_for, &return_status, 0);
		if (wait_ret_value == ERROR)
			return (ERROR);
		if (WIFSIGNALED(return_status))
			current_node->return_status = get_signal_return_status(return_status);
		else
			current_node->return_status = WEXITSTATUS(return_status);
		current_node = current_node->next;
	}
	return (SUCCESS);
}

static int	get_signal_return_status(int return_status)
{
	int	signo;

	signo = WTERMSIG(return_status);
	if (signo == SIGINT)
		return (130);
	if (signo == SIGQUIT)
		return (131);
	return (0);
}
