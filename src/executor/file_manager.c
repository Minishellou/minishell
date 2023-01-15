/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:57:57 by mcorso            #+#    #+#             */
/*   Updated: 2023/01/15 02:27:38 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file_to_read(char *file_path)
{
	int	ret_fd;

	ret_fd = open(file_path, O_RDONLY);
	if (ret_fd < 0)
		return (ERROR);
	return (ret_fd);
}

int	open_file_to_trunc(char *file_path)
{
	int	ret_fd;
	int	flags;
	int	access;

	flags = O_WRONLY | O_TRUNC | O_CREAT;
	access = S_IRUSR | S_IWUSR | S_IXUSR;
	ret_fd = open(file_path, flags, access);
	if (ret_fd < 0)
		return (ERROR);
	return (ret_fd);
}

int	open_file_to_append(char *file_path)
{
	int	ret_fd;
	int	flags;
	int	access;

	flags = O_WRONLY | O_APPEND | O_CREAT;
	access = S_IRUSR | S_IWUSR | S_IXUSR;
	ret_fd = open(file_path, flags, access);
	if (ret_fd < 0)
		return (ERROR);
	return (ret_fd);
}

void	write_to_file(int file_fd, char *string_to_write)
{
	size_t	string_len;

	if (string_to_write == NULL)
		return ;
	string_len = ft_strlen(string_to_write);
	write(file_fd, string_to_write, string_len);
}
