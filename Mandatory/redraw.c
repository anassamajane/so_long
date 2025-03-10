#include "game.h"

void	redraw_all_collectibles(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->collectibles_img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	redraw_door(t_game *game)
{
	int     x;
        int     y;

        y = 0;
        while (y < game->map_height)
        {
                x = 0;
                while (x < game->map_width)
                {
                        if (game->map[y][x] == 'E')
                                mlx_put_image_to_window(game->mlx, game->mlx_window, game->door_img, x * TILE_SIZE, y * TILE_SIZE);
                        x++;
                }
                y++;
        }
}
