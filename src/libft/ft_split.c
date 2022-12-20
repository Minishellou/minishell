/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:35:59 by gkitoko           #+#    #+#             */
/*   Updated: 2022/12/20 11:57:03 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c)
{
    if (c == ' ' || c == '\t'|| c == '\r')
        return (1);
    return (0);
}

static int	ft_countwords(char const *str)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	if (!str)
		return (0);
	while (str[i] && ft_ischarset(str[i]))
		i++;
	if (i >= (int)ft_strlen(str))
		return (0);
	while (str[i])
	{
		wc++;
		while (str[i] && !ft_ischarset(str[i]))
			i++;
		while (str[i] && ft_ischarset(str[i]))
			i++;
	}
	return (wc);
}

static char	*ft_dup(char const *str)
{
	int		len;
	int		i;
	char	*cpy;

	len = 0;
	i = 0;
	while (str[len] && !ft_ischarset(str[len]))
		len++;
	cpy = ft_malloc(sizeof(char) * len + 1);
	if (!cpy)
		return (NULL);
	while (str[i] && !ft_ischarset(str[i]))
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split(char const *s)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = (char **)ft_malloc(sizeof(char *) * (ft_countwords(s) + 1));
	if (!split)
		return (NULL);
	while (s[i] && ft_ischarset(s[i]))
		i++;
	while (s[i])
	{
		split[j] = ft_dup(&s[i]);
		while (s[i] && !ft_ischarset(s[i]))
			i++;
		while (s[i] && ft_ischarset(s[i]))
			i++;
		j++;
	}
	split[j] = 0;
	return (split);
}