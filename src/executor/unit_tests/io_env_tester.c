/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_env_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:07:35 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/07 11:36:24 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/unit_tests.h"

static void	fill_one_redir(int type, char *file_path)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)create_redirection(file_path);
	redirection->type = type;
	redirection->next = NULL;
	g_glo.redirection_table = redirection;
}

static int	open_to_write(char *file_path)
{
	int	output_fd;

	output_fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
	return (output_fd);
}

void	io_env_tester(void)
{
	int					output_fd;
	t_io_environment	test_io_env;

	PRINT_HEADER_TEST("EMPTY REDIRECTION CHAIN");
	test_io_env = io_environment_manager();
	null_input_redir_test(test_io_env.input_fd);
	null_output_redir_test(test_io_env.output_fd);
	PRINT_HEADER_TEST("SINGLE REDIRECTION CHAIN");
	fill_one_redir(OUPUT, "./src/executor/unit_tests/testfile.txt");
	test_io_env = io_environment_manager();
	output_fd = open_to_write("./src/executor/unit_tests/testfile.txt");
	single_output_redir_test(test_io_env.output_fd, output_fd);
}
