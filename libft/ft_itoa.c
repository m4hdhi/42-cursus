/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:16:11 by mamuzamm          #+#    #+#             */
/*   Updated: 2025/01/10 17:04:00 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_number_size(int number)
{
	unsigned int	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length += 1;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	length;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	length = ft_number_size(n);
	string = (char *)malloc(sizeof(char) * (length + 1));
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		n = -n;
	}
	if (n == 0)
		string[0] = '0';
	string[length] = '\0';
	while (n != 0)
	{
		string[length - 1] = (n % 10) + '0';
		n = n / 10;
		length--;
	}
	return (string);
}
