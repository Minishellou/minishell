/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:21:10 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 05:26:22 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	printf("%s\n", buffer);
	free(buffer);
}
