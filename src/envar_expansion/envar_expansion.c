/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:46:54 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/17 13:45:24 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env_node	*get_question_mark(void);

t_env_node	*get_envar(char *envar_name)
{
	size_t		envar_name_len;
	t_env_node	env;
	t_env_node	*current_node;

	if (ft_strcmp(envar_name, "$?") == SUCCESS)
		return (get_question_mark());
	env.next = g_glo.env;
	current_node = &env;
	envar_name_len = ft_strlen(envar_name) - 1;
	while (1)
	{
		current_node = current_node->next;
		if (!current_node)
			break ;
		if (ft_strncmp(current_node->name, envar_name + 1, envar_name_len))
			continue ;
		if (envar_name_len != ft_strlen(current_node->name))
			continue ;
		break ;
	}
	return (current_node);
}

char	*expand_envar_in_string(char *word)
{
	t_lexer_node	*env_list;
	t_lexer_node	*tmp;
	t_env_node		*current_var;

	if (!word)
		return (NULL);
	env_list = lexer_envar(word);
	tmp = env_list;
	if (!env_list)
		return (NULL);
	while (tmp)
	{
		if (check_and_get_envar(&tmp, &current_var) == SUCCESS)
			tmp = tmp->next;
	}
	return (concat_chain_to_string(env_list));
}

t_lexer_node	*envar_expansion(void)
{
	t_lexer_node	*tmp;

	if (!g_glo.lexer_output_chain)
		return (NULL);
	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "<<") == SUCCESS)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (ft_strchr(tmp->word, '$'))
		{
			tmp->word = expand_envar_in_string(tmp->word);
			if (tmp->word == NULL)
				tmp->word = "\0";
		}
		tmp = tmp->next;
	}
	return (g_glo.lexer_output_chain);
}

static t_env_node	*get_question_mark(void)
{
	char		*value;
	t_env_node	*ret_node;

	value = ft_itoa(g_glo.ret_status);
	if (!value)
		return (NULL);
	ret_node = (t_env_node *)create_env_node(NULL);
	ret_node->name = NULL;
	ret_node->value = value;
	return (ret_node);
}
