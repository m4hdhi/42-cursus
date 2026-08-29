/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:22:40 by mamuzamm          #+#    #+#             */
/*   Updated: 2025/02/24 22:27:11 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putchar(char c);
int	ft_uputnbr(unsigned int n);
int	flag_p(void *ptr);
int	ft_printf(const char *s, ...);
int	dtoh(unsigned long long int num, int flag);

#endif
