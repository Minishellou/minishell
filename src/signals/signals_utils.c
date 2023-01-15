/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:55:24 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 22:04:58 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_glo.ret_status = 130;
	}
}

void	sigquit_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		write(2, "ok\n", 3);
		write(2, "\b\b  \b\b", 6);
	}
}

void	sigquit_fork_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		exit(131);
	}
}

void	ctrld_handler(char *input)
{
	if (input == NULL)
	{
		ft_putstr_fd("exit", 2);
		exit_minishell(g_glo.ret_status);
	}
}

void	interrupt_cmd(int signo)
{
	(void)signo;
	write(2, "\n", 1);
	exit(130);
}