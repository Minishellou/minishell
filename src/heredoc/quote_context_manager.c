/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_context_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:42:39 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/14 13:08:50 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unquote_string(char **string)
{
	char	*cur_char;
	char	**splited_string;

	cur_char = *string;
	while (*cur_char != SINGLE_QUOTE && *cur_char != DOUBLE_QUOTE
		&& *cur_char != '\0')
		cur_char++;
	if (*cur_char == '\0')
		return (0);
	splited_string = ft_split(*string, *cur_char);
	*string = concat_array_to_string(splited_string);
	if (*string == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	unquoted_lexer_output_chain(void)
{
	t_lexer_node	*tmp;

	if (!g_glo.lexer_output_chain)
		return (ERROR);
	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		if (ft_strchr(tmp->word, SINGLE_QUOTE) || ft_strchr(tmp->word,
				DOUBLE_QUOTE))
		{
			if ((unquote_string(&tmp->word)) != SUCCESS)
				return (ERROR);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	is_quoted(char *string, int nb_of_quote)
{
	static char	first_quote = 0;

	if (*string == '\0')
	{
		if (nb_of_quote == 2 || nb_of_quote == 0)
			return (nb_of_quote == 2);
		else
			return (ERROR);
	}
	if (*string != '"' && *string != '\'')
		return (is_quoted(string + 1, nb_of_quote));
	if (nb_of_quote == 0)
		first_quote = *string;
	if (*string != first_quote)
		return (is_quoted(string + 1, nb_of_quote));
	return (is_quoted(string + 1, nb_of_quote + 1));
}
