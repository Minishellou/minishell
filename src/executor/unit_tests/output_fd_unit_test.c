/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_fd_unit_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:06:57 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/07 11:10:13 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/unit_tests.h"

void	null_output_redir_test(int output_fd)
{
	int	nb_of_test;

	nb_of_test = 0;
	PRINT_HEADER_TEST("OUTPUT_FD");
	nb_of_test++;
	PRINT_TEST(nb_of_test, "output_fd is returned not set");
	finder_returns_not_set(find_last_output_redir);
	nb_of_test++;
	PRINT_TEST(nb_of_test, "output_fd is only writable");
	fd_is_open_write(output_fd);
	nb_of_test++;
	PRINT_TEST(nb_of_test, "output_fd is duplicate of STDOUT");
	fds_are_duplicates(STDOUT, output_fd);
}

void	single_output_redir_test(int output_fd, int right_fd)
{
	int	nb_of_test;

	nb_of_test = 0;
	PRINT_HEADER_TEST("OUTPUT_FD");
	PRINT_TEST(0, "checking right file fd...")
	fd_is_open_write(right_fd);
	nb_of_test++;
	PRINT_TEST(nb_of_test, "output_fd is returned set");
	finder_returns_fd(find_last_output_redir);
	nb_of_test++;
	PRINT_TEST(nb_of_test, "output_fd is only writable");
	fd_is_open_write(output_fd);
	nb_of_test++;
	PRINT_TEST(nb_of_test, "output_fd is opened on right file");
	fds_are_duplicates(output_fd, right_fd);
}
