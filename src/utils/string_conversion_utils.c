/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_conversion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:18:45 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 09:19:35 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*concat_array_to_string(char **splited_string)
{
	int		i;
	int		len;
	char	*concatened_string;

	i = 1;
	len = 0;
	if (splited_string == NULL)
		return (NULL);
	concatened_string = *splited_string;
	while (splited_string[len] != NULL)
		len++;
	while (i < len)
	{
		concatened_string = ft_strjoin(concatened_string, splited_string[i]);
		i++;
	}
	return (concatened_string);
}
