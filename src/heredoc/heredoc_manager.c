/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:53:14 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/17 14:50:53 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_process(char *limit_string, int heredoc_fd);
static int	fork_heredoc_process(char *limit_string, int heredoc_fd);
static char	*get_current_tmpfile(void);

int	exec_every_heredoc_of_pipeline(t_exec_node *current_node)
{
	int				ret_status;
	t_redirection	*current_redir_chain;

	while (current_node != NULL)
	{
		current_redir_chain = current_node->redir_chain;
		while (current_redir_chain != NULL)
		{
			if (current_redir_chain->type == HEREDOC)
			{
				ret_status = manage_heredoc(current_redir_chain);
				if (ret_status != SUCCESS)
					return (ret_status);
			}
			current_redir_chain = current_redir_chain->next;
		}
		current_node = current_node->next;
	}
	return (SUCCESS);
}

int	manage_heredoc(t_redirection *heredoc_node)
{
	int		ret_status;
	int		tmpfile_fd;
	char	*tmpfile;

	tmpfile = get_current_tmpfile();
	if (tmpfile == NULL)
		return (ERROR);
	tmpfile_fd = open_file_to_trunc(tmpfile);
	if (tmpfile_fd == ERROR)
		return (ERROR);
	ret_status = fork_heredoc_process(heredoc_node->argument, tmpfile_fd);
	heredoc_node->type = INPUT;
	heredoc_node->argument = tmpfile;
	return (ret_status);
}

static int	fork_heredoc_process(char *limit_string, int heredoc_fd)
{
	int		heredoc_status;
	int		fork_pid;
	int		ret_status;

	fork_pid = fork();
	if (fork_pid == 0)
	{
		heredoc_sig();
		heredoc_status = heredoc_process(limit_string, heredoc_fd);
		close(heredoc_fd);
		if (heredoc_status != SUCCESS)
			exit_minishell(EXIT_FAILURE);
		exit_minishell(EXIT_SUCCESS);
	}
	close(heredoc_fd);
	if (waitpid(fork_pid, &ret_status, 0) == ERROR)
		return (ERROR);
	if (WIFSIGNALED(ret_status))
		return (WTERMSIG(ret_status));
	return (WEXITSTATUS(ret_status));
}

static int	heredoc_process(char *limit_string, int heredoc_fd)
{
	char			*current_string;
	t_quote_context	quote_context;

	if (process_limit_string(&limit_string, &quote_context) != SUCCESS)
		return (ERROR);
	while (1)
	{
		current_string = readline("heredoc> ");
		if (current_string == NULL)
			break ;
		if (*current_string == '\0' && limit_string == NULL)
			break ;
		if (limit_string == NULL)
			continue ;
		if (ft_strcmp(current_string, limit_string) == 0)
			break ;
		if (quote_context == UNQUOTED)
			current_string = expand_envar_in_string(current_string);
		write_to_file(heredoc_fd, current_string);
		write_to_file(heredoc_fd, "\n");
		free(current_string);
	}
	if (current_string == NULL)
		return (display_eof_error(limit_string), SUCCESS);
	return (free(current_string), SUCCESS);
}

static char	*get_current_tmpfile(void)
{
	char		*to_test;
	const char	*base_path;
	static int	index;

	base_path = "/tmp/.heredoc";
	to_test = ft_strjoin(base_path, ft_itoa(index++));
	while (access(to_test, F_OK) != ERROR)
		to_test = ft_strjoin(base_path, ft_itoa(index++));
	return (to_test);
}
