/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_env_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:07:35 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/06 16:52:53 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/unit_tests.h"

static
void	null_output_redir_test(int output_fd);

static
void	null_input_redir_test(int input_fd);

void	io_env_tester(void)
{
	t_io_environment	test_io_env;

	test_io_env = io_environment_manager();
	PRINT_HEADER_TEST("EMPTY REDIRECTION CHAIN");
	null_input_redir_test(test_io_env.input_fd);
	null_output_redir_test(test_io_env.output_fd);
}

static
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

static
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