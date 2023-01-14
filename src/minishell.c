/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/14 11:05:26 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_glo;

void	print_word_list(t_lexer_node *node)
{
	t_lexer_node  *tmp;

	if (node == NULL)
		return ;
	tmp = node;
	while (tmp)
	{
		printf("%s ->\n", tmp->word);
		tmp = tmp->next;
	}
}

void printf_redir_chain(t_redirection *node)
{
	t_redirection *tmp;
	
	if (!node)
		return ;
	tmp = node;
	while (tmp)
	{
		printf("type %d\n", tmp->type);
		printf("argument-> %s\n", tmp->argument);
		tmp = tmp->next;
	}
}

/*
static
void	print_env_list(t_env_node *node)
{
	if (node == NULL)
		return ;
	printf("%s = %s \n", node->name, node->value);
	print_env_list(node->next);
}
*/
static
int ft_exit(char *str)
{
  	if (!ft_strncmp(str, "exit", 4))
	{
		ft_free();
		return (ERROR);
	}
	return (SUCCESS);
}

void	main_process(char *str)
{
	if (process_lexer_output_chain(str) != SUCCESS)
		return ;
	g_glo.execution_chain = composer();
	if (exec_process_manager() != SUCCESS)
		return ;
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)av;
	if (init_global(envp) == ERROR)
		return (ERROR);
	if (ac > 1)
		return (printf("minishell binary does not take any argument.\n"), 0);
	while (1)
	{
		str = readline("minishell~ ");
		add_history(str);
		if(ft_exit(str) != SUCCESS)
		{
			ft_free();
			free(str);
			break ; 
		}
		main_process(str);
		g_glo.lexer_output_chain = NULL;
		g_glo.execution_chain = NULL;
		free(str);
		//print_word_list(g_glo.lexer_output_chain);
	}
	ft_free();
	return (0);
}