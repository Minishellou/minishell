/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:53:17 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/15 06:31:49 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_new_envar(char **to_add);
static int	manage_export(char **to_export);
static int	check_current_arg_validity(t_lexer_node *current_node);

int	export(int arg_number, t_lexer_node *arg_list)
{
	char	**export_split;

	while (arg_number > 0 && arg_list != NULL)
	{
		if (check_current_arg_validity(arg_list) != SUCCESS)
		{
			arg_list = arg_list->next;
			continue ;
		}
		export_split = ft_split(arg_list->word, '=');
		if (!export_split)
			return (12);
		if (manage_export(export_split) != SUCCESS)
			return (12);
		arg_list = arg_list->next;
	}
	return (SUCCESS);
}

static int	manage_export(char **to_export)
{
	int			plus_index;
	t_env_node	*environment;

	environment = g_glo.env;
	plus_index = NOT_SET;
	if (ft_strchr(to_export[0], '+') != NULL)
	{
		plus_index = ft_strlen(to_export[0]) - 2;
		to_export[0][plus_index] = '\0';
	}
	while (environment && ft_strcmp(environment->name, to_export[0]) != 0)
		environment = environment->next;
	if (environment && plus_index == NOT_SET)
		environment->value = to_export[1];
	if (environment && plus_index != NOT_SET)
	{
		environment->value = ft_strjoin(environment->value, to_export[1]);
		if (!environment->value)
			return (ERROR);
	}
	if (!environment)
		if (add_new_envar(to_export) == ERROR)
			return (ERROR);
	return (SUCCESS);
}

static int	add_new_envar(char **to_add)
{
	char		*envar_name;
	char		*envar_value;
	char		*envar_joined;
	t_env_node	*new_node;

	envar_name = to_add[0];
	envar_value = to_add[1];
	envar_joined = ft_strjoin(envar_name, "=");
	if (!envar_joined)
		return (ERROR);
	envar_joined = ft_strjoin(envar_joined, envar_value);
	if (!envar_joined)
		return (ERROR);
	new_node = (t_env_node *)create_env_node(envar_joined);
	if (!new_node)
		return (ERROR);
	append_to_chain((t_node **)&g_glo.env, (t_node *)new_node);
	return (SUCCESS);
}

static int	check_current_arg_validity(t_lexer_node *current_node)
{
	int		i;
	char	*current_arg;

	i = 0;
	current_arg = current_node->word;
	if (!current_arg)
		return (ERROR);
	if (!ft_isalpha(*current_arg))
		return (ERROR);
	while (ft_isalnum(current_arg[i]))
		i++;
	if (current_arg[i] == '\0')
		return (ERROR);
	if (current_arg[i] == '+' && current_arg[i + 1] == '=')
		return (SUCCESS);
	if (current_arg[i] == '=')
		return (SUCCESS);
	return (ERROR);
}
