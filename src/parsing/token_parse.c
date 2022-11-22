/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:44:12 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/21 15:21:11 by gkitoko          ###   ########.fr       */
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
		if (!token_state(state))
			return (0);
		if (!token_state_management(&i, &input, &state))
			return (0);
		if (input[i] != GREAT && input[i] != LESS && input[i] != PIPE)
			token_state_init(&state);
		i++;
	}
	return (1);
}

static int parse_error(char *input)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!input)
		return (0);
	len = ft_strlen(input) - 1;
	while (input[i] && is_white_space(input[i]))
		i++;
	if (is_special_token(input[i]))
		return (0);
	while(input[len] && is_white_space(input[len]))
		len--;
	if (is_special_token(input[len]))
		return (0);
	return (1);
}

int parse_token(char *input)
{
	if (!parse_error(input))
	{
		printf("parse error\n");
		return (0);	
	}
	if(!token_validation(input))
	{
		printf("token failure\n");
		return (0);	
	}
	return (1);
}