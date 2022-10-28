/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 13:48:50 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct S_garbage
{

    void        *addr;
    struct S_garbage   *next;

} t_garbage;

//t_garbage *garbage = NULL;

//GARBAGE COLLECTOR//
void* ft_malloc(int len, t_garbage** genisis_block);
void ft_free(t_garbage* genisis_block);
t_garbage* new_lst(void *addr);
t_garbage* ft_lstlast(t_garbage *genisis_block);
void    lst_addback(t_garbage **alst, t_garbage *new);

#endif