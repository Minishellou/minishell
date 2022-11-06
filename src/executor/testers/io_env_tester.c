/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_env_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:07:35 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/06 11:48:00 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PRINT_VALID_TEST(x) printf("\033[0;32m%s\n\033[0m", x)
#define	PRINT_FAILED_TEST(x) printf("\033[0;33m%s\n\033[0m", x)
#define STDIN g_glo.standard_input
#define STDOUT g_glo.standard_output


#include "../../../includes/minishell.h"

void	io_env_tester(void)
{

}

void	null_output_redir_test(void)
{
	int				output_fd;
	int				test_pipe[2];
	t_redirection	first_node;

	pipe(test_pipe);
	first_node = NULL;
	output_fd = find_last_output_redir(&first_node);
	dup2(fd[0], STDOUT);
	close(fd[0]);
	write(fd[1], "test\n", 5);
}