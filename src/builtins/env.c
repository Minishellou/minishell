/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:23:52 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 06:24:51 by mcorso           ###   ########.fr       */
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
	while (current_node != NULL)
	{
		current_envar = env_node_to_string(current_node);
		if (current_envar == NULL)
			return (ERROR);
		ft_putstr_fd(current_envar, 1);
		write(1, "\n", 1);
		current_node = current_node->next;
	}
	return (SUCCESS);
}
