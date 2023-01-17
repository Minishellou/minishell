/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_to_lexer_extend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:02:58 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/17 13:53:24 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*negate_envar(char *envar);

int	check_and_get_envar(t_lexer_node **tmp, t_env_node **current_var)
{
	char	*new_word;

	new_word = NULL;
	if (ft_strncmp((*tmp)->word, "$", ft_strlen((*tmp)->word)) == SUCCESS)
	{
		(*tmp) = (*tmp)->next;
		return (ERROR);
	}
	else if (ft_strchr((*tmp)->word, '$'))
	{
		(*current_var) = get_envar((*tmp)->word);
		if (*current_var)
			new_word = (*current_var)->value;
		if (!new_word)
		{
			(*tmp)->word = NULL;
			return (SUCCESS);
		}
		(*tmp)->word = ft_strdup(new_word);
		if (!(*tmp)->word)
			exit_minishell(12);
		(*tmp)->word = negate_envar((*tmp)->word);
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
		while (env_node[*i] && is_valid_env_char(env_node[*i]))
			if (env_node[(*i)++] == '?')
				break ;
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

static char	*negate_envar(char *envar)
{
	int	i;

	i = 0;
	while (envar[i] != '\0')
	{
		if (envar[i] == '"' || envar[i] == '\'')
			envar[i] *= -1;
		i++;
	}
	return (envar);
}
