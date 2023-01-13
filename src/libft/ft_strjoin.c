/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:50:00 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/13 17:55:54 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*n_str;
	size_t	l;
	size_t	a;

	l = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	i = 0;
	a = 0;
	n_str = ft_malloc(sizeof(char ) * (l + 1));
	if (!n_str)
		return (NULL);
	while (i < l)
	{
		if (i < ft_strlen((char *)s1))
			n_str[i] = s1[i];
		else
		{
			n_str[i] = s2[a];
			a++;
		}
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}
