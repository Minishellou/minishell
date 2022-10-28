/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:15:28 by gkitoko           #+#    #+#             */
/*   Updated: 2022/01/05 14:55:26 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*str1;
	const char	*str2;
	int			i;
	int			size;

	if (!dest && !src)
		return (NULL);
	str1 = dest;
	str2 = src;
	size = (int) n;
	i = 0;
	while (i < size)
	{
		str1[i] = str2[i];
		i++;
	}
	dest = str1;
	return (dest);
}
