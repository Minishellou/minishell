/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:27:27 by mcorso            #+#    #+#             */
/*   Updated: 2022/12/14 15:33:06 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_node_value(t_node	*node)
{
	char		*ret_value;
	t_env_node	*env_node;

	env_node = (t_env_node *)node;
	ret_value = ft_strjoin(env_node->name, "=");
	if (!ret_value)
		return (NULL);
	ret_value = ft_strjoin(ret_value, env_node->value);
	return (ret_value);
}

char	*get_lexer_node_value(t_node *node)
{
	char			*ret_value;
	t_lexer_node	*lexer_node;

	lexer_node = (t_lexer_node *)node;
	ret_value = lexer_node->word;
	return (ret_value);
}
