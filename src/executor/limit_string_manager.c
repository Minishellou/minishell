/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_string_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:05:16 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 09:44:43 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_quote_context	set_quote_context(char *limit_string)
{
	int				is_quoted_ret;

	is_quoted_ret = is_quoted(limit_string, 0);
	if (is_quoted_ret == 0)
		return (UNQUOTED);
	if (is_quoted_ret == 1)
		return (QUOTED);
	return (ERROR);
}

int	manage_limit_string(char **limit_string, int *quote_context)
{
	mask_escaped_char(limit_string);
	*quote_context = set_quote_context(*limit_string);
	if (*quote_context == ERROR)
		return (ERROR);
	if (unquote_string(limit_string) < 0)
		return (ERROR);
	if (delete_escaped_char(limit_string) < 0)
		return (ERROR);
	restore_escaped_char(limit_string);
	return (SUCCESS);
}
