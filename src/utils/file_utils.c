/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:57:57 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/16 11:53:22 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file_to_read(char *file_path)
{
	int	ret_fd;

	ret_fd = open(file_path, O_RDONLY);
	if (ret_fd < 0)
		printf("minishell: %s: %s\n", strerror(errno), file_path);
	return (ret_fd);
}

int	open_tmp_file(void)
{
	int	tmp_file;

	tmp_file = open("./tmp_file", TMP_FILE_FLAGS, TMP_FILE_ACCESS);
	if (tmp_file > 0)
		unlink("./tmp_file");
	return (tmp_file);
}

int	open_file_to_trunc(char *file_path)
{
	int	ret_fd;

	ret_fd = open(file_path, TRUNC_FILE_FLAGS, CREAT_FILE_ACCESS);
	if (ret_fd < 0)
		printf("minishell: %s: %s\n", strerror(errno), file_path);
	return (ret_fd);
}

int	open_file_to_append(char *file_path)
{
	int	ret_fd;

	ret_fd = open(file_path, APPND_FILE_FLAGS, CREAT_FILE_ACCESS);
	if (ret_fd < 0)
		printf("minishell: %s: %s\n", strerror(errno), file_path);
	return (ret_fd);
}

void	write_to_file(int file_fd, char *string_to_write)
{
	size_t	string_len;

	string_len = ft_strlen(string_to_write);
	write(file_fd, string_to_write, string_len);
	write(file_fd, "\n", 1);
}