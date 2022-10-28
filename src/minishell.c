/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 16:51:00 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//t_garbage *garbage = NULL;

int main(int ac, char **av)
{
	(void)av;
	
	if (ac > 1)
		return(printf("minishell binary does not take any argument.\n"), 0);
	char *str;
	int i = 0;

	while(1)
	{
		str = readline("minishell~ ");
		add_history(str);
		lexer(str);
		if (str[i] == 'x')
		{
			break;
		}
		printf("%s", str);
		printf("\n");
	}
	return (0);
}
