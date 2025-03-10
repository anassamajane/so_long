/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 06:46:04 by anaamaja          #+#    #+#             */
/*   Updated: 2024/11/14 08:23:39 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char			c;

	if (n < 0)
	{
		write (fd, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	c = nb % 10 + '0';
	if (nb >= 10)
		ft_putnbr_fd((nb / 10), fd);
	write (fd, &c, 1);
}
