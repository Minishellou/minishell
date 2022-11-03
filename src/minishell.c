/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/03 11:31:15 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_glo;

void	print_word_list(t_lexer_node *node)
{
	if (node == NULL)
		return ;
	printf("%s ->\n", node->word);
	print_word_list(node->next);
}

static
void	print_env_list(t_env_node *node)
{
	if (node == NULL)
		return ;
	printf("%s ->\n", node->var);
	print_env_list(node->next);
}


int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)av;
	init_global(envp);
	if (ac > 1)
		return (printf("minishell binary does not take any argument.\n"), 0);
	print_env_list(g_glo.env);
	while (1)
	{
		str = readline("minishell~ ");
		add_history(str);
		lexer(str);
		print_word_list(g_glo.lexer_output_chain);
	}
	ft_free();
	return (0);
}
