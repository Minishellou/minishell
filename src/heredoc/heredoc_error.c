/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:00:36 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/17 11:04:36 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_eof_error(char *limit_string)
{
	ft_putstr_fd("\nwarning: END-OF-FILE received (waiting for ", 2);
	if (!limit_string)
		ft_putstr_fd("[null]", 2);
	else
	{
		write(2, "'", 1);
		ft_putstr_fd(limit_string, 2);
		write(2, "'", 1);
	}
	write(2, ")\n", 2);
}
