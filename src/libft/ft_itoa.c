/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:40:55 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/15 02:02:07 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	count_nbr(long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (count + 1);
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			count;
	char		*buffer;

	nb = n;
	count = 0;
	count += count_nbr(nb);
	buffer = (char *)ft_malloc(sizeof(char) * (count + 1));
	if (!buffer)
		return (NULL);
	buffer[count] = '\0';
	if (nb == 0)
		buffer[0] = '0';
	if (nb < 0)
	{
		buffer[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		buffer[(count--) - 1] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (buffer);
}
