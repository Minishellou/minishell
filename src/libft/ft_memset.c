/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:23:13 by gkitoko           #+#    #+#             */
/*   Updated: 2021/11/26 16:18:08 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*str2;
	int		i;
	int		size;

	i = 0;
	size = (int) n;
	str2 = str;
	while (i < size)
	{
		str2[i] = c;
		i++;
	}
	str = str2;
	return (str);
}
