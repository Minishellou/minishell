/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:55:24 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/16 12:12:19 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_glo.ret_status = 130;
	}
}

void	sigquit_handler(int signo)
{
	if (signo == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

void	runtime_sigint_handler(int signo)
{
	if (signo == SIGINT)
		write(1, "\n", 1);
}

void	ctrld_handler(char *input)
{
	if (input == NULL)
	{
		ft_putstr_fd("exit", 2);
		exit_minishell(g_glo.ret_status);
	}
}
