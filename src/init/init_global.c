/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:01:49 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 00:15:39 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	increment_shlvl(void);
static int	dup_standard_fd(void);
static void	init_environment(void);

void	token_state_init(t_token_state *state)
{
	state->less = false;
	state->great = false;
	state->lesser = false;
	state->greater = false;
	state->pipe = false;
}

int	init_global(char **envp)
{
	g_glo.pipe_buff[0] = NOT_SET;
	g_glo.pipe_buff[1] = NOT_SET;
	g_glo.current_in_file = NOT_SET;
	g_glo.current_out_file = NOT_SET;
	if (dup_standard_fd() == ERROR)
		return (ERROR);
	g_glo.garbage_ctr = NULL;
	g_glo.env = NULL;
	if (*envp == NULL)
		init_environment();
	else
		g_glo.env = (t_env_node *)make_chain_from_array(envp, create_env_node);
	if (g_glo.env == NULL)
		return (ERROR);
	increment_shlvl();
	g_glo.ret_status = 0;
	g_glo.lexer_output_chain = NULL;
	g_glo.execution_chain = NULL;
	return (SUCCESS);
}

static int	dup_standard_fd(void)
{
	int	stdin;
	int	stdout;

	stdin = dup(0);
	stdout = dup(1);
	if (stdin != ERROR && stdout != ERROR)
	{
		g_glo.standard_input = stdin;
		g_glo.standard_output = stdout;
		return (SUCCESS);
	}
	if (stdin != ERROR)
		close(stdin);
	if (stdout != ERROR)
		close(stdout);
	return (ERROR);
}

static void	init_environment(void)
{
	char		*pwd_value;
	char		*shlvl;

	shlvl = ft_strdup("SHLVL=0");
	pwd_value = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!pwd_value)
		return ;
	append_to_chain((t_node **)&g_glo.env, create_env_node(pwd_value));
	append_to_chain((t_node **)&g_glo.env, create_env_node(shlvl));
}

static void	increment_shlvl(void)
{
	int			shlvl;
	t_env_node	*environment;

	environment = g_glo.env;
	while (ft_strcmp(environment->name, "SHLVL"))
		environment = environment->next;
	shlvl = ft_atoi(environment->value);
	environment->value = ft_itoa(shlvl + 1);
}
