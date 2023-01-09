/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:53:14 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/08 15:48:59 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_current_tmpfile(void);
static int	heredoc_process(char *limit_string, int heredoc_fd);

int	manage_heredoc(t_redirection *heredoc_node)
{
	int		tmpfile_fd;
	char	*tmpfile;

	tmpfile = get_current_tmpfile();
	if (tmpfile == NULL)
		return (ERROR);
	tmpfile_fd = open_file_to_trunc(tmpfile);
	if (tmpfile_fd == ERROR)
		return (ERROR);
	if (heredoc_process(heredoc_node->argument, tmpfile_fd) != SUCCESS)
		return (ERROR);
	heredoc_node->type = INPUT;
	heredoc_node->argument = tmpfile;
	return (SUCCESS);
}

int	exec_every_heredoc_of_pipeline(t_exec_node *current_node)
{
	t_redirection	*current_redir_chain;

	while (current_node != NULL)
	{
		current_redir_chain = current_node->redir_chain;
		while (current_redir_chain != NULL)
		{
			if (current_redir_chain->type == HEREDOC)
				if (manage_heredoc(current_redir_chain) != SUCCESS)
					return (ERROR);
			current_redir_chain = current_redir_chain->next;
		}
		current_node = current_node->next;
	}
	return (SUCCESS);
}

static char	*get_current_tmpfile(void)
{
	char		*to_test;
	const char	*base_path = "/tmp/.heredoc";
	static int	index;

	to_test = ft_strjoin(base_path, ft_itoa(index++));
	while (access(to_test, F_OK) != ERROR)
		to_test = ft_strjoin(base_path, ft_itoa(index++));
	return (to_test);
}

static int	heredoc_process(char *limit_string, int heredoc_fd)
{
	char			*current_string;
	size_t			limit_string_len;
	t_quote_context	quote_context;

	limit_string_len = ft_strlen(limit_string);
	if (process_limit_string(&limit_string, &quote_context) != SUCCESS)
		return (ERROR);
	while (1)
	{
		current_string = readline("heredoc> ");
		if (ft_strncmp(current_string, limit_string, limit_string_len) == 0)
			break ;
//		if (quote_context == UNQUOTED)
//			process_heredoc_string(current_string);
		write_to_file(heredoc_fd, current_string);
		write_to_file(heredoc_fd, "\n");
	}
	return (SUCCESS);
}
