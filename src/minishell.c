/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/06 11:48:24 by mcorso           ###   ########.fr       */
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
	printf("%s = %s \n", node->name, node->value);
	print_env_list(node->next);
}


int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)av;
	if (init_global(envp) == ERROR)
		return (ERROR);
	if (ac > 1)
		return (printf("minishell binary does not take any argument.\n"), 0);

	// print_env_list(g_glo.env);
	// while (1)
	// {
	// 	str = readline("minishell~ ");
	// 	add_history(str);
	// 	lexer(str);
	// 	print_word_list(g_glo.lexer_output_chain);
	// }
	null_output_redir_test();
	ft_free();
	return (SUCCESS);
}
