/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:20:48 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/16 19:05:42 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_env_node(char *var, t_env_node *node);

t_node	*create_lexer_node(char *word)
{
	t_lexer_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->word = "\0";
	if (word)
		new_node->word = word;
	new_node->next = NULL;
	return ((t_node *)new_node);
}

t_node	*create_env_node(char *var)
{
	t_env_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	fill_env_node(var, new_node);
	new_node->next = NULL;
	return ((t_node *)new_node);
}

t_node	*create_redirection(char *argument)
{
	t_redirection	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->argument = argument;
	new_node->next = NULL;
	return ((t_node *)new_node);
}

t_node	*create_exec_node(char *word)
{
	t_exec_node	*new_node;

	new_node = ft_malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->command_path = word;
	new_node->arg_chain = NULL;
	new_node->redir_chain = NULL;
	new_node->io_env.input = NOT_SET;
	new_node->io_env.output = NOT_SET;
	new_node->process_id = NOT_SET;
	new_node->return_status = NOT_SET;
	new_node->next = NULL;
	return ((t_node *)new_node);
}

static void	fill_env_node(char *var, t_env_node *node)
{
	int	i;

	i = 0;
	if (!var)
		return ;
	while (var[i] && var[i] != '=')
		i++;
	var[i] = '\0';
	node->name = var;
	node->value = &var[i + 1];
	return ;
}
