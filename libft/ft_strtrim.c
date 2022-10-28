/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:15:47 by gkitoko           #+#    #+#             */
/*   Updated: 2022/01/11 13:48:02 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_set(char s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	len_trim(char const *s1, char const *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i] && is_set(s1[i], set))
	{
		count++;
		i++;
	}
	i = (int) ft_strlen(s1) - 1;
	while (i >= 0 && is_set(s1[i], set))
	{
		count++;
		i--;
	}
	if ((count / 2) == (int)ft_strlen(s1))
		return (0);
	return ((int)ft_strlen(s1) - count);
}

char	*new_string(char const *s1, char const *set, int i, int len)
{
	int		a;
	char	*res;

	a = 0;
	if (!s1 && !set)
	{
		res = ft_strdup("");
		return (res);
	}
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (a < len)
	{
		res[a] = s1[i];
		a++;
		i++;
	}
	res[a] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*buffer;
	size_t	i;
	size_t	l;

	i = 0;
	l = len_trim(s1, set);
	while (s1[i] && is_set(s1[i], set))
		i++;
	buffer = new_string(s1, set, i, l);
	return (buffer);
}
