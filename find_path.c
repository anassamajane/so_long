#include "game.h"

char	**copy_map(t_game *game)
{
	char	**map_copy;
	int	y;

	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		exit(1);
	y = 0;
	while (y < game->map_height)
	{
		map_copy[y] = strdup(game->map[y]);
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
	if (map[y][x] == '1' || map[y][x] == 'V')
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
	int	x;
	int	y;

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
				printf("Error: No valid path to collect all items and reach the exit\n");
				exit (1);
			}
			x++;
		}
		y++;
	}
}
