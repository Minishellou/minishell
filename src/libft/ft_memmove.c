/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:33:48 by gkitoko           #+#    #+#             */
/*   Updated: 2021/12/02 13:44:20 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	char		*dest;
	const char	*src;
	size_t		i;

	dest = str1;
	src = str2;
	i = 0;
	if (src > dest)
	{
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else if (src < dest)
	{
		while (n > 0)
		{
			dest[n - 1] = src[n - 1];
			n--;
		}
	}
	str1 = dest;
	return (str1);
}
