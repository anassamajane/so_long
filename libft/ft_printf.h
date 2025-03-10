/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:46:01 by anaamaja          #+#    #+#             */
/*   Updated: 2024/12/06 11:35:24 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# define LOWER16 "0123456789abcdef"
# define UPPER16 "0123456789ABCDEF"
# define BASE10 "0123456789"

int	ft_printf(const char *str, ...);
int	ft_check(va_list args, char c);
int	ft_putnbr_base(unsigned long nbr, char *str, int base);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	ft_putnbr_unsigned(unsigned int nbr);
int	ft_hexa_lower(unsigned int nbr);
int	ft_hexa_upper(unsigned int nbr);
int	ft_address(unsigned long nbr);
#endif
