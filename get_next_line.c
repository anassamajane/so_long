/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:33:51 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/06 23:36:55 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	*read_helper(int fd, char *remainder, char *buffer)
{
	ssize_t	bytes_read;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!remainder)
			remainder = ft_strdup(buffer);
		else
			remainder = ft_strjoin(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (free(remainder), (remainder = NULL), NULL);
	return (remainder);
}

char	*read_and_store(int fd, char *remainder)
{
	char	*buffer;

	if (remainder && ft_strchr(remainder, '\n'))
		return (remainder);
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	remainder = read_helper(fd, remainder, buffer);
	free(buffer);
	return (remainder);
}

char	*extract_line(char *remainder)
{
	char	*line;
	char	*newline_pos;

	if (!remainder)
		return (NULL);
	newline_pos = ft_strchr(remainder, '\n');
	if (newline_pos)
		line = ft_substr(remainder, 0, (newline_pos - remainder + 1));
	else
		line = ft_strdup(remainder);
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*newline_pos;
	char	*new_remainder;

	if (!remainder)
		return (NULL);
	newline_pos = ft_strchr(remainder, '\n');
	new_remainder = NULL;
	if (newline_pos)
	{
		if (*(newline_pos + 1))
			new_remainder = ft_strdup(newline_pos + 1);
		free(remainder);
		return (new_remainder);
	}
	free(remainder);
	remainder = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_and_store(fd, remainder);
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}
