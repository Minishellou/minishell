/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_string_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:05:16 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/14 12:57:47 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_quote_context	set_quote_context(char *limit_string);

int	process_limit_string(char **limit_string, int *quote_context)
{
	*quote_context = set_quote_context(*limit_string);
	if (*quote_context == ERROR)
		return (ERROR);
	if (unquote_string(limit_string) < 0)
		return (ERROR);
	return (SUCCESS);
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
