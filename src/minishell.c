/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/01 13:15:47 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global global;

int main(int ac, char **av, char **envp)
{
	(void)av;
	(void)envp;
	init_global();
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
	ft_free();
	return (0);
}
