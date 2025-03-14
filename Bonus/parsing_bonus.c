/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:26:30 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/11 00:55:18 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void	free_map_before_exit(t_game *game, int height, char *msg)
{
	ft_free(game->map, height);
	get_next_line(-1);
	ft_printf("Error\n");
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

int	count_lines(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nThere is no file by this name\n");
		exit(1);
	}
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (count);
}

void	allocate_map(t_game *game, const char *filename)
{
	game->map_height = count_lines(filename);
	if (game->map_height <= 0)
	{
		ft_printf("Error\nInvalid map: ");
		ft_printf("The file is empty or could not be read\n");
		exit(1);
	}
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
	{
		ft_printf("Error\nMemory Allocation Failed\n");
		exit(1);
	}
}

void	read_and_validate_lines(int fd, t_game *game)
{
	int (i), (width);
	i = 0;
	game->map_width = 0;
	while (i < game->map_height)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
			free_map_before_exit(game, i, "Failed to read map file");
		if (i == 0)
		{
			while (game->map[i][game->map_width] && \
					game->map[i][game->map_width] != '\n')
				game->map_width++;
		}
		else
		{
			width = 0;
			while (game->map[i][width] && game->map[i][width] != '\n')
				width++;
			if (width != game->map_width)
				free_map_before_exit(game, i + 1, "Map is not rectangular");
		}
		i++;
	}
	game->map[i] = NULL;
}

void	read_map(const char *filename, t_game *game)
{
	int	fd;

	allocate_map(game, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCould not open the file\n");
		free(game->map);
		exit(1);
	}
	read_and_validate_lines(fd, game);
	close (fd);
}
