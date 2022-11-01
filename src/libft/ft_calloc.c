/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:05:36 by gkitoko           #+#    #+#             */
/*   Updated: 2021/12/20 14:07:43 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t size)
{
	char	*ptr;

	ptr = (char *) malloc(elementCount * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, elementCount * size);
	return ((void *)ptr);
}
