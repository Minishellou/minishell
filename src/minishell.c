/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:25:24 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/17 14:53:19 by mcorso           ###   ########.fr       */
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
//	
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
	ft_free();
	close(g_glo.standard_input);
	close(g_glo.standard_output);
	exit(exit_status);
}

static char	*read_command_line(char *prompt)
{
	char			*str;
	char			*read_line;

	read_line = readline(prompt);
	ctrld_handler(read_line);
	if (*read_line == '\0')
	{
		free(read_line);
		return (NULL);
	}
	str = ft_strdup(read_line);
	free(read_line);
	return (str);
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

static void	process_and_execute_command(char *command)
{
	int	heredoc_status;

	if (process_lexer_output_chain(command) != SUCCESS)
	{
		g_glo.ret_status = 2;
		return ;
	}
	g_glo.execution_chain = composer();
	ignore_sig();
	heredoc_status = exec_every_heredoc_of_pipeline(g_glo.execution_chain);
	if (heredoc_status == ERROR)
		exit_minishell(EXIT_FAILURE);
	if (heredoc_status != SUCCESS)
	{
		if (heredoc_status == 2)
			g_glo.ret_status = 130;
		write(1, "\n", 1);
		return ;
	}
	if (exec_process_manager() == ERROR)
		exit_minishell(EXIT_FAILURE);
	set_return_status();
	if (g_glo.ret_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	return ;
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
	{
		return \
		(ft_putstr_fd("lmao, do you even know what you're doing?\n", 2), \
		SUCCESS);
	}
	while (1)
	{
		init_sig();
		str = read_command_line("minishell~ ");
		if (str == NULL)
			continue ;
		add_history(str);
		process_and_execute_command(str);
		g_glo.lexer_output_chain = NULL;
		g_glo.execution_chain = NULL;
	}
	return (0);
}
