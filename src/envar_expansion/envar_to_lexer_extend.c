/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_to_lexer_extend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:02:58 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 17:05:09 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_and_get_envar(t_lexer_node **tmp, t_env_node **current_var)
{
	if (ft_strncmp((*tmp)->word, "$", ft_strlen((*tmp)->word)) == SUCCESS)
	{
		(*tmp) = (*tmp)->next;
		return (ERROR);
	}
	else if (ft_strchr((*tmp)->word, '$'))
	{
		(*current_var) = get_envar((*tmp)->word);
		if ((*current_var))
			(*tmp)->word = (*current_var)->value;
		else
			(*tmp)->word = NULL;
	}
	return (SUCCESS);
}

int	check_and_add_var(char *env_node, t_lexer_node **node, int *i)
{
	if (env_node[*i] == '$')
	{
		*node = add_env_list(&env_node[*i], *node);
		if (!*node)
			return (ERROR);
		(*i)++;
		while (env_node[*i] && \
					(is_valid_env_char(env_node[*i])))
			(*i)++;
	}
	else
	{
		*node = add_env_list(&env_node[*i], *node);
		if (!*node)
			return (ERROR);
		while (env_node[*i] && env_node[*i] != '$')
			(*i)++;
	}
	return (SUCCESS);
}
