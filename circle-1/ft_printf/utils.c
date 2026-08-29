/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:22:57 by mamuzamm          #+#    #+#             */
/*   Updated: 2025/02/24 22:27:11 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	dtoh(unsigned long long int num, int flag)
{
	unsigned long long	n;
	char				*str;
	char				*str2;

	n = 0;
	str = "0123456789abcdef";
	str2 = "0123456789ABCDEF";
	if (num >= 16)
		n += dtoh(num / 16, flag);
	if (flag == 'x')
		n += write(1, &str[num % 16], 1);
	else if (flag == 'X')
		n += write(1, &str2[num % 16], 1);
	return ((int)n);
}

int	flag_p(void *ptr)
{
	int	n;

	n = 0;
	if (ptr == NULL)
		return (write(1, "0x0", 3));
	n += write(1, "0x", 2);
	n += dtoh((unsigned long)ptr, 'x');
	return (n);
}

int	ft_uputnbr(unsigned int n)
{
	char			a;
	char			b;
	unsigned int	num;

	num = 0;
	if (n <= 9)
	{
		a = n + '0';
		num += write(1, &a, 1);
	}
	else
	{
		num += ft_uputnbr(n / 10);
		b = (n % 10) + '0';
		num += write(1, &b, 1);
	}
	return (num);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}
