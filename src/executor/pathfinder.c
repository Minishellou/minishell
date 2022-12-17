/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 22:43:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/17 22:49:51 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_path(char **env_paths, char *command);

char	*pathfinder_process(char *command)
{
	char		*final_path;
	char		**env_paths;
	t_env_node	*path_env_node;

	final_path = command;
	path_env_node = get_envar("$PATH");
	if (path_env_node)
		env_paths = ft_split(path_env_node->value, ':');
	if (path_env_node && !env_paths)
		return (NULL);
	if (env_paths)
		final_path = find_path(env_paths, command);
	return (final_path);
}

char	*find_path(char **env_paths, char *command)
{
	int		i;
	char	*current_test;

	i = 0;
	while (env_paths[i] != NULL)
	{
		current_test = ft_strjoin(env_paths[i], command);
		if (!current_test)
			return (NULL);
		if (access(current_test, F_OK) == SUCCESS)
			return (current_test);
		i++;
	}
	return (command);
}
