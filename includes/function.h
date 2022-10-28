/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:19:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/10/28 21:02:06 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "./struct.h"


/*		GARBAGE COLLECTOR		*/
//	Init
void			lst_addback(t_garbage_node **alst, t_garbage_node *new_block);
t_garbage_node	*new_lst(void *addr);
t_garbage_node	*ft_lstlast(t_garbage_node *genisis_block);
//	Collect garbage
void			*ft_malloc(int len, t_garbage_node **genisis_block);
//	Throw garbage
void			ft_free(t_garbage_node *genisis_block);

#endif