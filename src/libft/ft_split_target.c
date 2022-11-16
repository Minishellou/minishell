/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_target.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:29:25 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/16 15:35:31 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istarget(char c, char target)
{
    if (c == target)
        return (1);
    return (0);
}

static int	ft_countwords_target(char const *str, char sep)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	while (str[i] && ft_istarget(str[i], sep))
		i++;
	while (str[i])
	{
		wc++;
		while (str[i] && !ft_istarget(str[i], sep))
			i++;
		while (str[i] && ft_istarget(str[i], sep))
			i++;
	}
	return (wc);
}

static char	*ft_dup_target(char const *str, char target)
{
	int		len;
	int		i;
	char	*cpy;

	len = 0;
	i = 0;
	while (str[len] && !ft_target(str[len], target))
		len++;
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (str[i] && !ft_istarget(str[i], target))
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split_target(char const *s, char target)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = (char **)malloc(sizeof(char *) * (ft_countwords_target(s, target) + 1));
	if (!split)
		return (NULL);
	while (s[i] && ft_istarget(s[i], target))
		i++;
	while (s[i])
	{
		split[j] = ft_dup_target(&s[i]);
		while (s[i] && !ft_istarget(s[i], target))
			i++;
		while (s[i] && ft_istarget(s[i], target))
			i++;
		j++;
	}
	split[j] = 0;
	return (split);
}
