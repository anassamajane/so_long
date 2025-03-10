/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:35:20 by anaamaja          #+#    #+#             */
/*   Updated: 2024/11/15 22:54:16 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t n)
{
	char	*src;
	char	*dest;
	size_t	i;

	i = 0;
	if (!to && !from)
		return (NULL);
	if (from == to)
		return (to);
	src = (char *) from;
	dest = (char *) to;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (to);
}
