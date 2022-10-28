/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:19:17 by gkitoko           #+#    #+#             */
/*   Updated: 2021/12/06 11:58:34 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*conv_str;
	int		i;

	conv_str = (char *) str;
	i = 0;
	while (conv_str[i] != '\0')
	{
		if (conv_str[i] == (char)c)
		{
			return (&conv_str[i]);
		}
		i++;
	}
	if (conv_str[i] == '\0' && (char)c == '\0')
	{
		return (&conv_str[i]);
	}
	return (NULL);
}
