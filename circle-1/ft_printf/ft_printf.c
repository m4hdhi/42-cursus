/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:22:32 by mamuzamm          #+#    #+#             */
/*   Updated: 2025/02/24 22:27:11 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putnbr(int n)
{
	char	a;
	char	b;
	int		num;

	num = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		num += write(1, "-", 1);
		n *= -1;
	}
	if (n >= 0 && n <= 9)
	{
		a = n + '0';
		num += write(1, &a, 1);
	}
	else
	{
		num += ft_putnbr(n / 10);
		b = (n % 10) + '0';
		num += write(1, &b, 1);
	}
	return (num);
}

int	ft_putstr(char *s)
{
	int		num;
	size_t	i;

	i = 0;
	num = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i] != '\0')
	{
		num += write(1, &s[i], 1);
		i++;
	}
	return (num);
}

int	ft_valhelp(char specifier, va_list args)
{
	int	num;

	num = 0;
	if (specifier == 'c')
		num += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		num += ft_putstr(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		num += ft_putnbr(va_arg(args, int));
	else if (specifier == '%')
		num += ft_putchar('%');
	else if (specifier == 'x' || specifier == 'X')
		num += dtoh(va_arg(args, unsigned int), specifier);
	else if (specifier == 'p')
		num += flag_p(va_arg(args, void *));
	else if (specifier == 'u')
		num += ft_uputnbr(va_arg(args, unsigned int));
	return (num);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		num;

	va_start(args, s);
	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			num += ft_valhelp(s[i], args);
		}
		else
			num += ft_putchar(s[i]);
		if (s[i])
			i++;
	}
	va_end(args);
	return (num);
}
