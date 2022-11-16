/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:53:14 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 09:03:06 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_process(char *limit_string)
{
	int				tmp_file;
	char			*current_string;
	t_quote_context	quote_context;

	if (manage_limit_string(&limit_string, &quote_context) != SUCCESS)
		return (ERROR);
	tmp_file = open_tmp_file();
	while (1)
	{
		current_string = readline("heredoc> ");
		if (ft_strcmp(current_string, limit_string) == 0)
			break ;
//		if (quote_context == UNQUOTED)
//			process_heredoc_string(current_string);
		write_to_file(tmp_file, current_string);
	}
	return (tmp_file);
}
