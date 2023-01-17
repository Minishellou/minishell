/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:49:45 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/17 15:41:12 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_pwd_envar(char *cwd);
static int	create_old_pwd_envar(char *old_pwd);
static int	update_related_envar(char *new_cwd, char *old_cwd);
static int	update_old_pwd_envar(char *old_pwd);

int	cd(int arg_number, t_lexer_node *arg_chain)
{
	char		*old_pwd;
	char		*arg_path;
	t_env_node	*home_var;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (12);
	if (arg_number > 1)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	home_var = get_envar("$HOME");
	if (arg_number == 0)
	{
		if (!home_var)
			return (ft_putstr_fd("cd : HOME is not set\n", 2), 1);
		return (chdir(home_var->value));
	}
	else
	{
		arg_path = arg_chain->word;
		if (chdir(arg_path) != SUCCESS)
			return (perror(arg_path), 2);
	}
	if (update_related_envar(getcwd(NULL, 0), old_pwd) != SUCCESS)
		return (12);
	return (SUCCESS);
}

static int	update_related_envar(char *new_cwd, char *old_pwd)
{
	int			ret_status;
	t_env_node	*environment;

	if (!new_cwd)
		return (ERROR);
	environment = g_glo.env;
	while (environment && \
	ft_strcmp(environment->name, "PWD") != SUCCESS)
		environment = environment->next;
	if (environment)
		environment->value = ft_strdup(new_cwd);
	else
		if (create_pwd_envar(new_cwd) != SUCCESS)
			return (ERROR);
	ret_status = update_old_pwd_envar(old_pwd);
	if (new_cwd)
		free(new_cwd);
	if (old_pwd)
		free(old_pwd);
	return (ret_status);
}

static int	update_old_pwd_envar(char *old_pwd)
{
	t_env_node	*environment;

	environment = g_glo.env;
	while (environment && \
			ft_strcmp(environment->name, "OLDPWD") != SUCCESS)
		environment = environment->next;
	if (environment)
		environment->value = ft_strdup(old_pwd);
	else
		if (create_old_pwd_envar(old_pwd) != SUCCESS)
			return (ERROR);
	return (SUCCESS);
}

static int	create_old_pwd_envar(char *old_pwd)
{
	char		*env_node_value;
	t_env_node	*new_node;

	env_node_value = ft_strjoin("OLDPWD=", old_pwd);
	if (!env_node_value)
		return (ERROR);
	new_node = (t_env_node *)create_env_node(env_node_value);
	if (!new_node)
		return (ERROR);
	append_to_chain((t_node **)&g_glo.env, (t_node *)new_node);
	return (SUCCESS);
}

static int	create_pwd_envar(char *cwd)
{
	char		*env_node_value;
	t_env_node	*new_node;

	env_node_value = ft_strjoin("PWD=", cwd);
	if (!env_node_value)
		return (ERROR);
	new_node = (t_env_node *)create_env_node(env_node_value);
	if (!new_node)
		return (ERROR);
	append_to_chain((t_node **)&g_glo.env, (t_node *)new_node);
	return (SUCCESS);
}
