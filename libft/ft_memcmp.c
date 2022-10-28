/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:06:42 by gkitoko           #+#    #+#             */
/*   Updated: 2021/12/02 14:09:25 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;
	char	*str;
	char	*second_str;

	i = 0;
	str = (char *)str1;
	second_str = (char *)str2;
	while (i < n)
	{
		if (str[i] > second_str[i])
		{
			return ((unsigned char)str[i] - (unsigned char)second_str[i]);
		}
		if (str[i] < second_str[i])
		{
			return ((unsigned char)str[i] - (unsigned char)second_str[i]);
		}
		i++;
	}
	return (0);
}
