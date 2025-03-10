/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:52:57 by anaamaja          #+#    #+#             */
/*   Updated: 2024/12/05 16:31:42 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;
	int	result;

	if (str == NULL)
		return (write (1, "(null)", 6));
	i = 0;
	result = 0;
	while (str[i])
	{
		result = result + (write(1, &str[i], 1));
		i++;
	}
	return (result);
}
