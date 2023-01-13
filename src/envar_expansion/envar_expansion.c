/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:46:54 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/13 18:54:28 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*get_envar(char *envar_name)
{
	size_t		envar_name_len;
	t_env_node	env;
	t_env_node	*current_node;

	env.next = g_glo.env;
	current_node = &env;
	envar_name_len = ft_strlen(envar_name) - 1;
	while (1)
	{
		current_node = current_node->next;
		if (!current_node)
			break ;
		if (ft_strncmp(current_node->name, envar_name + 1, envar_name_len))
			continue;
		if (envar_name_len != ft_strlen(current_node->name))
			continue;
		break ;
	}
	return (current_node);
}

char *expand_envar_in_string(char *word)
{
	t_lexer_node *env_list;
	t_lexer_node *tmp;
	t_env_node *current_var;

	if (!word)
		return (NULL);
	env_list = lexer_envar(word);
	tmp = env_list;
	if (!env_list)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->word, "$", ft_strlen(tmp->word)) == SUCCESS)
		{
			tmp = tmp->next;
			continue ;
		}
		else if (ft_strchr(tmp->word, '$'))
		{
			current_var = get_envar(tmp->word);
			if (current_var)
				tmp->word = current_var->value;
			else
				tmp->word = NULL;
		}
		tmp = tmp->next;
	}
	return(concat_chain_to_string(env_list));
}

t_lexer_node *envar_expansion(void)
{
	t_lexer_node *tmp;

	if (!g_glo.lexer_output_chain)
		return (NULL);
	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		if (ft_strchr(tmp->word, '$'))
			tmp->word = expand_envar_in_string(tmp->word);
		tmp = tmp->next;
	}
	return(g_glo.lexer_output_chain);
}
