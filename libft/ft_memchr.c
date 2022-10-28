/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:18:37 by gkitoko           #+#    #+#             */
/*   Updated: 2022/01/05 14:25:06 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int search, size_t size)
{
	char	*conv_str;
	size_t	i;

	i = 0;
	conv_str = (void *)str;
	while (i < size)
	{
		if (conv_str[i] == (char)search)
		{
			return (&conv_str[i]);
		}
		i++;
	}
	return (NULL);
}
