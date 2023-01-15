/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:43:59 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/14 23:30:12 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_path(char **env_paths, char *command);
static char	*append_path_to_command(char *path, char *command);

int	is_command_a_path(char *command)
{
	int	index;

	index = -1;
	while (command[++index] != '\0')
		if (command[index] == '/')
			return (1);
	return (0);
}

char	*pathfinder_process(char *command)
{
	char		*final_path;
	char		**env_paths;
	t_env_node	*path_env_node;

	final_path = command;
	path_env_node = get_envar("$PATH");
	if (!path_env_node)
		return (command);
	if (path_env_node)
		env_paths = ft_split(path_env_node->value, ':');
	if (path_env_node && !env_paths)
		return (NULL);
	if (env_paths)
		final_path = find_path(env_paths, command);
	return (final_path);
}

static char	*find_path(char **env_paths, char *command)
{
	int		i;
	char	*current_test;

	i = 0;
	while (env_paths[i] != NULL)
	{
		current_test = append_path_to_command(env_paths[i], command);
		if (!current_test)
			return (NULL);
		if (access(current_test, F_OK) == SUCCESS)
			return (current_test);
		i++;
	}
	return (command);
}

static char	*append_path_to_command(char *path, char *command)
{
	char	*ret_path;

	ret_path = ft_strjoin(path, "/");
	if (ret_path)
		ret_path = ft_strjoin(ret_path, command);
	return (ret_path);
}
