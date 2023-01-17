/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_string_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:05:16 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/17 12:04:05 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int				unquote_limit_string(char **limit_string);
static t_quote_context	set_quote_context(char *limit_string);

int	process_limit_string(char **limit_string, int *quote_context)
{
	*quote_context = set_quote_context(*limit_string);
	if (*quote_context == ERROR)
		return (ERROR);
	if (unquote_limit_string(limit_string) < 0)
		return (ERROR);
	return (SUCCESS);
}

static int	unquote_limit_string(char **limit_string)
{
	if (quote_neon(limit_string) != SUCCESS)
		return (ERROR);
	while (ft_strchr(*limit_string, SINGLE_QUOTE) || \
		ft_strchr(*limit_string, DOUBLE_QUOTE))
	{
		if ((unquote_string(limit_string)) != SUCCESS)
			return (ERROR);
	}
	return (reset_neg_char(limit_string));
}

static t_quote_context	set_quote_context(char *limit_string)
{
	int	is_quoted_ret;

	is_quoted_ret = is_quoted(limit_string, 0);
	if (is_quoted_ret == 0)
		return (UNQUOTED);
	if (is_quoted_ret == 1)
		return (QUOTED);
	return (ERROR);
}
