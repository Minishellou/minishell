/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/31 10:30:06 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

//t_garbage *garbage = NULL;

int main(int ac, char **av)
{
	(void)av;
	t_global *global;

	global = malloc(sizeof(t_global));
	global->garbage_collector = NULL;
	if (ac > 1)
		return(printf("minishell binary does not take any argument.\n"), 0);
	char *str;
	int i = 0;

	while(1)
	{
		str = readline("minishell~ ");
		add_history(str);
		lexer(str, &global);
		if (str[i] == 'x')
		{
			break;
		}
		printf("%s", str);
		printf("\n");
	}
	return (0);
}
