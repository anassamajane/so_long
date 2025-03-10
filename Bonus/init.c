#include "game.h"

int	init_game(t_game *game)
{
	int	img_width;
	int	img_height;

	game->mlx = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE + STEP_COUNTER_HEIGHT, "Map");

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "../textures/wall_floor/80wall.xpm", &img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "../textures/wall_floor/black_floor.xpm", &img_width, &img_height);
	if (load_player_images(game) || load_collectibles_images(game) || load_number_images(game) || load_enemy_images(game) || load_door_images(game))
		return (1);
	game->collected = 0;
	game->step_counter = 0;
	game->door_frame_index = 0;
	game->enemy_frame_index = 0;
	game->animation_counter = 0;
	game->collectibles_counter = 0;
	game->collectibles_frame_index = 0;
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->counter_bar, 0 * TILE_SIZE, 0 *TILE_SIZE);
	count_collectibles(game);
	return (0);
}

void	count_collectibles(t_game *game)
{
	game->total_collectibles = 0;
	for (int y = 0; y < game->map_height; y++)
	{
		for (int x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] == 'C')
				game->total_collectibles++;
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				game->prev_player_x = x;
				game->prev_player_y = y;
				//game->map[y][x] = '0';
			}
		}
	}
}
