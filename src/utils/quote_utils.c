/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:42:39 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 09:40:52 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unquote_string(char **string)
{
	char	*cur_char;
	char	**splited_string;

	cur_char = *string;
	while (*cur_char != '\'' && *cur_char != '"' && *cur_char != '\0')
		cur_char++;
	if (*cur_char == '\0')
		return (0);
	splited_string = ft_split(*string, *cur_char);
	*string = concat_array_to_string(splited_string);
	if (*string == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	is_quoted(char *string, int nb_of_quote)
{
	static char	first_quote = 0;

	if (*string == '\0')
	{
		if (nb_of_quote == 2 || nb_of_quote == 0)
			return (nb_of_quote == 2);
		else
			return (ERROR);
	}
	if (*string == '\\')
		return (is_quoted(string + 2, nb_of_quote));
	if (*string != '"' && *string != '\'')
		return (is_quoted(string + 1, nb_of_quote));
	if (nb_of_quote == 0)
		first_quote = *string;
	if (*string != first_quote)
		return (is_quoted(string + 1, nb_of_quote));
	return (is_quoted(string + 1, nb_of_quote + 1));
}
