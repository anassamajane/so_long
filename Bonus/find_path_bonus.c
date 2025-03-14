/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:34:57 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/11 00:54:00 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void	ft_free(char **map_copy, int rows)
{
	if (!map_copy)
		return ;
	while (rows > 0)
		free(map_copy[--rows]);
	free(map_copy);
}

char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		y;

	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		exit(1);
	y = 0;
	while (y < game->map_height)
	{
		map_copy[y] = ft_strdup(game->map[y]);
		if (!map_copy[y])
			exit(1);
		y++;
	}
	map_copy[y] = NULL;
	return (map_copy);
}

void	find_player_position(t_game *game, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'X')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	validate_path(t_game *game)
{
	char	**map_copy;

	int (x), (y);
	map_copy = copy_map(game);
	find_player_position(game, &x, &y);
	flood_fill(map_copy, x, y);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
			{
				ft_free(map_copy, game->map_height);
				ft_free(game->map, game->map_height);
				ft_printf("Error\nNo valid path to collect ");
				ft_printf("all items and reach the exit\n");
				exit (1);
			}
			x++;
		}
		y++;
	}
	ft_free(map_copy, game->map_height);
}
