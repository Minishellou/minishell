/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:44:12 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/09 12:50:41 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
int token_validation(char *input)
{
	int i;
	t_token_state state;
	
	i = 0;
	token_state_init(&state);
	while (input[i])
	{
		if (token_state(state) != SUCCESS)
			return (ERROR);
		if (token_state_management(&i, &input, &state) != SUCCESS)
			return (ERROR);
		if (input[i] != GREAT && input[i] != LESS && input[i] != PIPE)
			token_state_init(&state);
		i++;
	}
	return (SUCCESS);
}

static int parse_error(char *input)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!input)
		return (ERROR);
	len = ft_strlen(input) - 1;
	while (input[i] && (is_white_space(input[i]) != ERROR))
		i++;
	if (input[i] == '\0')
		return (SUCCESS);
	if (input[i] == PIPE)
		return (ERROR);
	while(input[len] && (is_white_space(input[len]) != ERROR))
		len--;
	if ((is_special_token(input[len])) == SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int parse_token(char *input)
{
	if ((parse_error(input)) != SUCCESS)
	{
		printf("parse error\n");
		return (ERROR);	
	}
	if((token_validation(input)) != SUCCESS)
	{
		printf("token failure\n");
		return (ERROR);	
	}
	return (SUCCESS);
}