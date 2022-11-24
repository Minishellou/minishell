/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:13:54 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/22 13:39:40 by gkitoko          ###   ########.fr       */
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
	if (state.pipe == true)
		checker++;
	if ( checker != 1 && checker != 0)
		return (ERROR);
	return (SUCCESS);
}

void switch_state(bool *old, bool *new)
{
	*old = false;
	*new = true;
}

int token_state_management(int *i, char **input, t_token_state *state)
{
	if ((*input)[(*i)] == GREAT)
	{
		if (state->great == true)
			switch_state(&state->great, &state->greater);
		else if (state->greater == true)
			return (ERROR);
		else 
			state->great = true;
	}
	if ((*input)[(*i)] == LESS)
	{
		if (state->less == true)
			switch_state(&state->less, &state->lesser);
		else if (state->lesser == true)
			return (ERROR);
		else 
			state->less = true;
	}
	if ((*input)[(*i)] == PIPE)
	{
		if (state->pipe == true)
			return (ERROR);
		state->pipe = true; 	
	}
	return (SUCCESS);
}