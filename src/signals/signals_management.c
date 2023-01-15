/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:50:53 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 22:04:29 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_sig(void)
{
	signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, sigquit_handler);
}

void	fork_sig(void)
{
	signal(SIGINT, interrupt_cmd);
	signal(SIGQUIT, sigquit_fork_handler);
}

void	ignore_sig(void)
{
	signal(SIGINT, SIG_IGN);
	//signal(SIGQUIT, SIG_IGN);
}
