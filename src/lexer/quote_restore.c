/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_restore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:47:45 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/17 12:32:30 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	positive(char **str)
{
	int		i;
	char	start;
	int		found;

	i = 1;
	found = 1;
	start = (*str)[0];
	while ((*str)[found] && (*str)[found] != start)
		found++;
	if ((*str)[found] != start)
		return (ERROR);
	while ((*str)[i] && (*str)[i] != start)
	{
		if ((*str)[i] < 0)
			(*str)[i] *= -1;
		i++;
	}
	return (i);
}

int	quote_positive(char **str, char c)
{
	int		i;
	int		return_index;
	char	*quoted_substring;

	i = 0;
	return_index = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] && ((*str)[i] == c))
		{
			quoted_substring = &(*str)[i];
			return_index = positive(&quoted_substring);
			if (return_index > 0)
				i += return_index;
			if (!(*str)[i])
				break ;
		}
		i++;
	}
	return (SUCCESS);
}

int	reset_neg_char(char **str)
{
	int	i;

	i = 0;
	if (!*str)
		return (ERROR);
	while ((*str)[i])
	{
		if ((*str)[i] < 0)
			(*str)[i] *= -1;
		i++;
	}
	return (SUCCESS);
}

int	reset_neg_char_in_lexer_output(void)
{
	t_lexer_node	*tmp;

	if (!g_glo.lexer_output_chain)
		return (ERROR);
	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		if (reset_neg_char(&tmp->word) != SUCCESS)
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	reset_double_quote_content_to_pst(void)
{
	t_lexer_node	*tmp;
	char			c;

	c = DOUBLE_QUOTE;
	if (!g_glo.lexer_output_chain)
		return (ERROR);
	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		quote_positive(&tmp->word, c);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
