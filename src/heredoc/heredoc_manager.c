/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:53:14 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 11:26:36 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_process(char *limit_string)
{
	int				tmp_file;
	char			*current_string;
	size_t			limit_string_len;
	t_quote_context	quote_context;

	if (manage_limit_string(&limit_string, &quote_context) != SUCCESS)
		return (ERROR);
	limit_string_len = ft_strlen(limit_string);
	tmp_file = open_tmp_file();
	if (tmp_file < 0)
		return (ERROR);
	while (1)
	{
		current_string = readline("heredoc> ");
		if (ft_strncmp(current_string, limit_string, limit_string_len) == 0)
			break ;
//		if (quote_context == UNQUOTED)
//			process_heredoc_string(current_string);
		write_to_file(tmp_file, current_string);
	}
	return (tmp_file);
}
