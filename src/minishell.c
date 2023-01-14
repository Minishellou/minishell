/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/14 21:46:38 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_glo;

/*
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


static
void	print_env_list(t_env_node *node)
{
	if (node == NULL)
		return ;
	printf("%s = %s \n", node->name, node->value);
	print_env_list(node->next);
}
*/

static void	exit_minishell(int exit_status)
{
	write(2, "\n", 1);
	ft_free();
	close(g_glo.standard_input);
	close(g_glo.standard_output);
	exit(exit_status);
}

static int	process_and_execute_command(char *command)
{
	int	new_ret_status;

	if (process_lexer_output_chain(command) != SUCCESS)
		return (2);
	g_glo.execution_chain = composer();
	new_ret_status = exec_process_manager();
	if (new_ret_status == ERROR)
		exit_minishell(EXIT_FAILURE);
	return (new_ret_status);
}

static char	*read_command_line(char *prompt)
{
	char			*str;
	t_garbage_node	*new_node;

	str = readline(prompt);
	if (str == NULL)
		exit_minishell(EXIT_SUCCESS);
	if (*str == '\0')
		return (NULL);
	new_node = new_grb_node(str);
	lst_addback(new_node);
	return (str);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)av;
	if (isatty(0) == 0)
		return (EXIT_FAILURE);
	if (!*envp)
		return (EXIT_SUCCESS);
	if (init_global(envp) == ERROR)
		return (EXIT_FAILURE);
	if (ac > 1)
		return (printf("minishell binary does not take any argument.\n"), 0);
	while (1)
	{
		str = read_command_line("minishell~ ");
		if (str == NULL)
			continue ;
		add_history(str);
		g_glo.ret_status = process_and_execute_command(str);
		g_glo.lexer_output_chain = NULL;
		g_glo.execution_chain = NULL;
	}
	return (0);
}
