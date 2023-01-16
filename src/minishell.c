/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:25:24 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/16 12:11:42 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

t_global	g_glo;

// void	print_word_list(t_lexer_node *node)
// {
// 	t_lexer_node  *tmp;

// 	if (node == NULL)
// 		return ;
// 	tmp = node;
// 	while (tmp)
// 	{
// 		printf("%s ->\n", tmp->word);
// 		tmp = tmp->next;
// 	}
// }

// void printf_redir_chain(t_redirection *node)
// {
// 	t_redirection *tmp;
	
// 	if (!node)
// 		return ;
// 	tmp = node;
// 	while (tmp)
// 	{
// 		printf("type %d\n", tmp->type);
// 		printf("argument-> %s\n", tmp->argument);
// 		tmp = tmp->next;
// 	}
// }

// static
// void	print_env_list(t_env_node *node)
// {
// 	if (node == NULL)
// 		return ;
// 	printf("%s=%s \n", node->name, node->value);
// 	print_env_list(node->next);
// }

void	exit_minishell(int exit_status)
{
	write(2, "\n", 1);
	ft_free();
	close(g_glo.standard_input);
	close(g_glo.standard_output);
	exit(exit_status);
}

static char	*read_command_line(char *prompt)
{
	char			*str;
	t_garbage_node	*new_node;

	str = readline(prompt);
	ctrld_handler(str);
	if (str == NULL)
		exit_minishell(EXIT_SUCCESS);
	if (*str == '\0')
		return (NULL);
	new_node = new_grb_node(str);
	lst_addback(new_node);
	return (str);
}

static void	process_and_execute_command(char *command)
{
	if (process_lexer_output_chain(command) != SUCCESS)
	{
		g_glo.ret_status = 2;
		return ;
	}
	g_glo.execution_chain = composer();
	if (exec_process_manager() == ERROR)
		exit_minishell(EXIT_FAILURE);
}

static void	set_return_status(void)
{
	t_exec_node	*current_node;

	current_node = g_glo.execution_chain;
	while (current_node)
	{
		if (current_node->return_status != NOT_SET)
			g_glo.ret_status = current_node->return_status;
		current_node = current_node->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)av;
	if (isatty(0) == 0)
		return (EXIT_FAILURE);
	if (init_global(envp) == ERROR)
		return (EXIT_FAILURE);
	if (ac > 1)
		return (printf("minishell binary does not take any argument.\n"), 0);
	while (1)
	{
		init_sig();
		str = read_command_line("minishell~ ");
		if (str == NULL)
			continue ;
		add_history(str);
		process_and_execute_command(str);
		set_return_status();
		if (g_glo.ret_status == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		g_glo.lexer_output_chain = NULL;
		g_glo.execution_chain = NULL;
	}
	return (0);
}
