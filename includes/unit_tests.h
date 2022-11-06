/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:03:36 by mcorso            #+#    #+#             */
/*   Updated: 2022/11/06 16:36:50 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TESTS_H
# define UNIT_TESTS_H

# define RESET printf("\033[0m");
# define	BOLD printf("\033[1m");
# define RED printf("\033[31m");
# define GREEN printf("\033[32m");

# define PRINT_HEADER_TEST(x) { BOLD printf("\n%s\n", x); RESET }
# define PRINT_TEST(x, y) { BOLD printf("\t%i - ", x); RESET printf("%s: ", y); }
# define PRINT_VALID_TEST { BOLD GREEN printf("OK\n"); RESET }
# define PRINT_FAILED_TEST { BOLD RED printf("KO\n"); RESET }
# define TEST_RESULT(boolean) if (boolean) PRINT_VALID_TEST else PRINT_FAILED_TEST; 
# define PERFECT(nb_test) { BOLD GREEN printf("\n\t%i/%i\n\n", nb_test); RESET }
# define NOT_PERFECT(nb_test) { BOLD RED printf("\n\t%i/%i\n\n", nb_test); RESET }

# define STDIN g_glo.standard_input
# define STDOUT g_glo.standard_output

#include "minishell.h"

//	IO ENV
void	fd_is_open_read(int fd);
void	fd_is_open_write(int fd);
void	fds_are_duplicates(int fd_one, int fd_two);
void	finder_returns_not_set(int (*finder)(t_redirection *));

#endif