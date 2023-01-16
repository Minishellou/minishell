/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:21:10 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/16 20:54:20 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	ft_putstr_fd(buffer, 1);
	free(buffer);
	return (SUCCESS);
}
