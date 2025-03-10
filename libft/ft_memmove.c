/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:44:44 by anaamaja          #+#    #+#             */
/*   Updated: 2024/11/14 05:16:17 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*from;
	char			*to;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	from = (char *) src;
	to = (char *) dst;
	if (to > from)
	{
		while (len-- > 0)
			to[len] = from[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			to[i] = from[i];
			i++;
		}
	}
	return (dst);
}
