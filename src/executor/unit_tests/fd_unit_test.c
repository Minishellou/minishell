/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_unit_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:03:13 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/07 09:53:11 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/unit_tests.h"

void	finder_returns_not_set(int (*finder)(t_redirection *))
{
	int	result;

	result = finder(g_glo.redirection_table);
	TEST_RESULT(result == NOT_SET);
}

void	finder_returns_fd(int (*finder)(t_redirection *))
{
	int	result;

	result = finder(g_glo.redirection_table);
	TEST_RESULT(result > -1);	
}

void	fd_is_open_write(int fd)
{
	int	result;

	result = write(fd, "", 0);
	TEST_RESULT(result > -1);
}

void	fd_is_open_read(int fd)
{
	char	buff[1];
	int	result;

	result = read(fd, buff, 0);
	TEST_RESULT(result > -1);
}

void	fds_are_duplicates(int fd_one, int fd_two)
{
	int	result;

	dup2(fd_one, fd_two);
	result = write(fd_two, "", 0);
	TEST_RESULT(result > -1);
}