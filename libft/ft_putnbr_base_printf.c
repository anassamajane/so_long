/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:34:20 by anaamaja          #+#    #+#             */
/*   Updated: 2024/12/06 20:25:12 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long nbr, char *str, int base)
{
	int	count;

	count = 0;
	if (nbr >= (unsigned long)base)
		count = ft_putnbr_base((nbr / (unsigned long)base), str, base);
	count += ft_putchar(str[(nbr % base)]);
	return (count);
}
