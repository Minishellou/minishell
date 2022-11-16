/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_char_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:39:07 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 09:02:49 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mask_escaped_char(char **string)
{
	int	i;

	i = 0;
	while ((*string)[i] != '\0')
		if ((*string)[i++] == '\\')
			(*string)[i] *= -1;
}

int	delete_escaped_char(char **string)
{
	char	**splited_string;

	splited_string = ft_split(*string, '\\');
	*string = concat_array_to_string(splited_string);
	if (*string == NULL)
		return (ERROR);
	return (SUCCESS);
}

void	restore_escaped_char(char **string)
{
	int	i;

	i = 0;
	while ((*string)[i] != '\0')
		if ((*string)[i] < 0)
			(*string)[i] *= -1;
}
