/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:35:29 by anaamaja          #+#    #+#             */
/*   Updated: 2024/11/11 13:29:57 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	word;
	int	count;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (word == 0)
			{
				word = 1;
				count++;
			}
		}
		else
			word = 0;
		i++;
	}
	return (count);
}

static int	ft_wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_wordcopy(char *dest, const char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_free(char **str, int i)
{
	while (i > 0)
		free (str[--i]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	int (len), (i), (words);
	if (!s)
		return (NULL);
	words = count_words(s, c);
	str = malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*s != '\0' && *s == c)
			s++;
		len = ft_wordlen(s, c);
		str[i] = malloc(sizeof(char) * (len + 1));
		if (!str[i])
			return (ft_free(str, i), NULL);
		ft_wordcopy(str[i], s, len);
		s += len;
	}
	str[i] = NULL;
	return (str);
}
