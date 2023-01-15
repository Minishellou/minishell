/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:34:13 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/15 18:13:12 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_exec_node *command)
{
	int		arg_count;
	char	*command_name;

	arg_count = get_chain_len((t_node *)command->arg_chain);
	command_name = command->command_path;
	if (ft_strcmp(command_name, "echo") == 0)
		return (echo(command->arg_chain));
	if (ft_strcmp(command_name, "cd") == 0)
		return (cd(arg_count, command->arg_chain));
	if (ft_strcmp(command_name, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(command_name, "export") == 0)
		return (export(arg_count, command->arg_chain));
	if (ft_strcmp(command_name, "unset") == 0)
		return (unset(command->arg_chain));
	if (ft_strcmp(command_name, "env") == 0)
		return (env());
	exit_builtins(arg_count, command->arg_chain);
	return (EXIT_FAILURE);
}

int	is_a_builtin(char *command_name)
{
	if (ft_strcmp(command_name, "echo") == 0)
		return (1);
	if (ft_strcmp(command_name, "cd") == 0)
		return (1);
	if (ft_strcmp(command_name, "pwd") == 0)
		return (1);
	if (ft_strcmp(command_name, "export") == 0)
		return (1);
	if (ft_strcmp(command_name, "unset") == 0)
		return (1);
	if (ft_strcmp(command_name, "env") == 0)
		return (1);
	if (ft_strcmp(command_name, "exit") == 0)
		return (1);
	return (0);
}
