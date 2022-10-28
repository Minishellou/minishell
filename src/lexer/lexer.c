/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 16:16:33 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void lexer(char *str)
{
	char **split;
	//t_parse parse;
	int i = 0;
	
	split = ft_split(str, ' ');
	while (split[i])
	{
		
	}
}