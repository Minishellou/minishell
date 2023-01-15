/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:14:50 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 07:36:00 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
int	search_for_option(t_lexer_node **arg_chain)
{
	while (*arg_chain != NULL && (*arg_chain)->word[0] == '-')
	{
		if (ft_strcmp("-n", (*arg_chain)->word) == 0)
		{
			*arg_chain = (*arg_chain)->next;
			return (1);
		}
		*arg_chain = (*arg_chain)->next;
	}
	return (0);
}

int	echo(t_lexer_node *arg_chain)
{
	int				no_newline_flag;
	t_lexer_node	*current_arg;

	if (!arg_chain)
	{
		write(1, "\n", 1);
		return (SUCCESS);
	}
	current_arg = arg_chain;
	no_newline_flag = search_for_option(&current_arg);
	while (current_arg)
	{
		ft_putstr_fd(current_arg->word, 1);
		current_arg = current_arg->next;
		if (current_arg)
			write(1, " ", 1);
	}
	if (!no_newline_flag)
		write(1, "\n", 1);
	return (SUCCESS);
}
