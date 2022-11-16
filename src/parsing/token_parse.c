/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:44:12 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/16 17:15:19 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int token_state(t_token_state state)
{
	int checker;

	checker = 0;
	if (state.less == true)
		checker++;
	if (state.great == true)
		checker++;
	if (state.lesser == true)
		checker++;
	if (state.greater == true)
		checker++;
	if(checker != 1 || checker != 0)
		return (0);
	return (1);
}

void switch_state(bool *old, bool *new)
{
	*old = false;
	*new = true;
}

int token_validation(char *input)
{
	int i;
	t_token_state state;
	
	i = 0;
	while (str[i])
	{
		if (!token_state(state))
			return (0);
		if (str[i] == GREAT)
		{
			if (state.great == true)
				switch_state(&state.great, &state.greater);			
			else 
				state.great = true;
		}
		if (str[i] == LESS)
		{
			if (state.less == true)
				switch_state(&state.less, &state.lesser);
			else 
				state.less = true;
		}
		i++;
	}
	return (1);
}
/*
int redict_ending_check(char *input)
{
	
}
*/

int	pipe_failure(char *input)
{
	int i;

	i = 0;
	if (!input)
		return (0);
	if (input[i] == PIPE)
		return (0);
	while (input[i])
		i++;
	if (str[i - 1] == PIPE)
		return (0)
	return (0);
}
/*
void parse_token()
*/