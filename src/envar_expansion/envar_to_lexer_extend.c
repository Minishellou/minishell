/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_to_lexer_extend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:02:58 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/13 18:48:50 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_and_add_var(char *env_node, t_lexer_node **node, int *i)
{
   if (env_node[*i] == '$')
   {
       *node = add_env_list(&env_node[*i], *node);
       if (!*node)
           return (ERROR);
       (*i)++;
       while (env_node[*i] && ft_isalnum(env_node[*i]))
           (*i)++;
   }
   else
   {
       *node = add_env_list(&env_node[*i], *node);
       if (!*node)
           return (ERROR);
       while (env_node[*i] && env_node[*i] != '$')
           (*i)++;
   }
  return (SUCCESS);
}