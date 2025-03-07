#include "game.h"

int	init_game(t_game *game)
{
	int	img_width;
	int	img_height;

	game->mlx = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx, MAP_WIDTH * TILE_SIZE, WINDOW_HEIGHT, "Map");

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall_floor/80wall.xpm", &img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "textures/wall_floor/black_floor.xpm", &img_width, &img_height);
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
	return (0);
}

void	init_map(t_game *game)
{
	char temp_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    		"111111111111111111111111111111111111",
    		"1E00000000X0000C00000C00000000000001",
    		"101001010010000010100100000001010101",
    		"101001001010101000100100000001010101",
    		"1P000X000C00C0000000000000000X000C01",
    		"101001010010000010100100000001010101",
    		"101001001010101000100100000001010101",
    		"1C00000000X0000C00000C00000000000C01",
    		"10000000000000000X00000000000X000001",
    		"111111111111111111111111111111111111"
	};
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			game->map[i][j] = temp_map[i][j];
	count_collectibles(game);
}

void	count_collectibles(t_game *game)
{
	game->total_collectibles = 0;
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
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
