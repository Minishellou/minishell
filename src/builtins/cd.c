/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:49:45 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/15 05:51:56 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_old_pwd_envar(char *old_pwd);
static int	update_related_envar(char *new_cwd);
static int	update_old_pwd_envar(char *old_pwd);

int	cd(int arg_number, t_lexer_node *arg_chain)
{
	char		*arg_path;
	t_env_node	*home_var;

	home_var = get_envar("$HOME");
	if (arg_number == 0)
	{
		if (!home_var)
			return (ft_putstr_fd("cd : HOME is not set", 2), 1);
		return (chdir(home_var->value));
	}
	else if (arg_number == 1)
	{
		arg_path = arg_chain->word;
		return (chdir(arg_path));
	}
	if (update_related_envar(getcwd(NULL, 0)) != SUCCESS)
		return (12);
	return (SUCCESS);
}

static int	update_related_envar(char *new_cwd)
{
	char		*old_pwd;
	t_env_node	*environment;

	environment = g_glo.env;
	while (ft_strcmp(environment->name, "PWD") != SUCCESS)
		environment = environment->next;
	old_pwd = environment->value;
	environment->value = new_cwd;
	update_old_pwd_envar(old_pwd);
}

static int	update_old_pwd_envar(char *old_pwd)
{
	t_env_node	*environment;

	environment = g_glo.env;
	while (ft_strcmp(environment->name, "OLD_PWD") != SUCCESS)
	{
		environment = environment->next;
		if (!environment)
			break ;
	}
	if (!environment)
		if (create_old_pwd_envar != SUCCESS)
			return (ERROR);
	environment->value = old_pwd;
	return (SUCCESS);
}

static int	create_old_pwd_envar(char *old_pwd)
{
	char		*env_node_value;
	t_env_node	*new_node;

	env_node_value = ft_strjoin("OLD_PWD=", old_pwd);
	if (!env_node_value)
		return (ERROR);
	new_node = (t_env_node *)create_env_node(env_node_value);
	if (!new_node)
		return (ERROR);
	append_to_chain(&g_glo.env, new_node);
	return (SUCCESS);
}
