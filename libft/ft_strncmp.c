/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:54:44 by gkitoko           #+#    #+#             */
/*   Updated: 2022/01/05 14:23:44 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
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
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
