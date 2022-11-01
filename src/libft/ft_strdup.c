/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:21:05 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/01 20:00:22 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*dup;
	int		i;

	i = 0;
	str = (char *) s;
	dup = (char *)ft_malloc(sizeof(char) * ft_strlen(str) + 1);
	if (dup == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
