/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:14:50 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/16 20:53:22 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//		fa
static
int	only__n(char *argument)
{
	int	i;

	i = 1;
	if (ft_strncmp("-n", argument, 2) != 0)
		return (0);
	while (argument[i] != '\0' && argument[i] == 'n')
		i++;
	if (argument[i] == '\0')
		return (1);
	return (0);
}

static
int	search_for_option(t_lexer_node **arg_chain)
{
	int	n_option;
	int	only_n_ret;

	n_option = 0;
	while (*arg_chain != NULL && (*arg_chain)->word[0] == '-')
	{
		only_n_ret = only__n((*arg_chain)->word);
		if (only_n_ret == 0)
			return (n_option);
		n_option = only_n_ret;
		*arg_chain = (*arg_chain)->next;
	}
	return (n_option);
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
