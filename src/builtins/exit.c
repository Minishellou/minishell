/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:16:47 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 05:34:33 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
int	find_alpha(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (ft_isalpha(word[i]))
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

void	exit_builtins(int arg_nb, t_lexer_node *arg_chain)
{
	int	argument;

	argument = 0;
	ft_putstr_fd("exit", 2);
	if (arg_nb == 0)
		exit_minishell(0);
	if (arg_nb != 1)
	{
		ft_putstr_fd("\nToo many arguments !", 2);
		return ;
	}
	if (ft_strlen(arg_chain->word) > 3)
	{
		ft_putstr_fd("\nmagic number required", 2);
		exit_minishell(2);
	}
	if (find_alpha(arg_chain->word) == SUCCESS)
	{
		ft_putstr_fd("\nnumerical operand required !", 2);
		exit_minishell(2);
	}
	argument = ft_atoi(arg_chain->word);
	if (argument < 0 && argument > 255)
		exit_minishell(255 - argument);
	exit_minishell(argument);
}