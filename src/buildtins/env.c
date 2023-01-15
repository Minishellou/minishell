/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:23:52 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 05:34:49 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
char	*env_node_to_string(t_env_node *current_node)
{
	char	*ret_string;
	char	*envar_name;
	char	*envar_value;

	envar_name = current_node->name;
	envar_value = current_node->value;
	ret_string = ft_strjoin(envar_name, "=");
	if (ret_string == NULL)
		return (NULL);
	ret_string = ft_strjoin(ret_string, envar_value);
	return (ret_string);
}

int	env(void)
{
	char		*current_envar;
	t_env_node	*current_node;

	current_node = g_glo.env;
	while (environment != NULL)
	{
		current_envar = env_node_to_string(current_node);
		if (current_envar == NULL)
			return (ERROR);
		ft_putstr_fd(1, current_envar);
		write(1, "\n", 1);
	}
	return (SUCCESS);
}
