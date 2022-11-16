/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_string_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:05:16 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 09:03:27 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_quote_context	set_quote_context(char *limit_string)
{
	t_quote_context	context;

	context = UNQUOTED;
	if (is_quoted(limit_string, 0))
		context = QUOTED;
	return (context);
}

static char	*concat_array_to_string(char **splited_string)
{
	int		i;
	int		len;
	char	*concatened_string;

	i = 1;
	len = 0;
	if (splited_string == NULL)
		return (NULL);
	concatened_string = *splited_string;
	while (splited_string[len] != NULL)
		len++;
	while (i < len)
	{
		concatened_string = ft_strjoin(concatened_string, splited_string[i]);
		i++;
	}
	return (concatened_string);
}

int	manage_limit_string(char **limit_string, int *quote_context)
{
	mask_escaped_char(limit_string);
	*quote_context = set_quote_context(*limit_string);
	if (unquote_string(limit_string) < 0)
		return (ERROR);
	if (delete_escape_char(limit_string) < 0)
		return (ERROR);
	restore_escaped_char(limit_string);
	return (SUCCESS);
}
