/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:26:10 by gkitoko           #+#    #+#             */
/*   Updated: 2021/12/08 11:30:47 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s) || s == NULL)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (new_str == NULL)
		return (NULL);
	while (i < len)
	{
		new_str[i] = (unsigned char)s[i + start];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
