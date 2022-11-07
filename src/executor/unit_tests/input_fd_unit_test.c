/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_fd_unit_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:06:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/07 10:09:28 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/unit_tests.h"

void	null_input_redir_test(int input_fd)
{
	int	nb_of_test;

	nb_of_test = 0;
	PRINT_HEADER_TEST("INPUT_FD");
	nb_of_test++;
	PRINT_TEST(nb_of_test, "input_fd is returned not set");
	finder_returns_not_set(find_last_input_redir);
	nb_of_test++;
	PRINT_TEST(nb_of_test, "input_fd is only readable");
	fd_is_open_read(input_fd);
	nb_of_test++;
	PRINT_TEST(nb_of_test, "input_fd is duplicate of STDIN");
	fds_are_duplicates(STDIN, input_fd);
}
