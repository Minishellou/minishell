/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:53:24 by gkitoko           #+#    #+#             */
/*   Updated: 2022/01/05 13:25:35 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	destsize;

	srcsize = ft_strlen((char *)src);
	destsize = ft_strlen(dst);
	if (size < destsize)
		return (srcsize + size);
	else
	{
		dst = dst + destsize;
		ft_strlcpy(dst, src, size - destsize);
		return (srcsize + destsize);
	}
}
