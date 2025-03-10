/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:36:01 by anaamaja          #+#    #+#             */
/*   Updated: 2024/11/11 13:31:32 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == (char)chr)
			return ((char *)str + i);
		i--;
	}
	if (str[0] == (char)chr)
		return ((char *)str + i);
	return (NULL);
}
