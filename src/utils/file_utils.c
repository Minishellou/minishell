/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:57:57 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 08:31:57 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_tmp_file(void)
{
	int	tmp_file;

	tmp_file = open("./tmp_file", O_RDWR | O_TRUNC | O_CREAT);
	if (tmp_file > 0)
		unlink(tmp_file);
	return (tmp_file)
}

void	write_to_file(int file_fd, char *string_to_write)
{
	size_t	string_len;

	string_len = ft_strlen(string_to_write);
	write(file_fd, string_to_write, string_len);
	write(file_fd, "\n", 1);
}