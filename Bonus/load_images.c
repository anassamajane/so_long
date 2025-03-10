#include "game.h"

int	load_player_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->player_up = mlx_xpm_file_to_image(game->mlx, "../textures/player/goku_up.xpm", &img_width, &img_height);
	game->player_down = mlx_xpm_file_to_image(game->mlx, "../textures/player/goku_down.xpm", &img_width, &img_height);
	game->player_left = mlx_xpm_file_to_image(game->mlx, "../textures/player/goku_left.xpm", &img_width, &img_height);
	game->player_right = mlx_xpm_file_to_image(game->mlx, "../textures/player/goku_right.xpm", &img_width, &img_height);
	game->dead_player = mlx_xpm_file_to_image(game->mlx, "../textures/player/dead_goku.xpm", &img_width, &img_height);
	game->current_player = game->player_right;
	//game.prev_player_x = game.player_x;
	//game.prev_player_y = game.player_y;
	return (0);
}

int	load_collectibles_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->collectible_frames[0] = mlx_xpm_file_to_image(game->mlx, "../textures/collectibles/Dragonball_up1.xpm", &img_width, &img_height);
	game->collectible_frames[1] = mlx_xpm_file_to_image(game->mlx, "../textures/collectibles/Dragonball_down.xpm", &img_width, &img_height);
	game->collectibles_img = game->collectible_frames[0];
	//game.collectibles_frame_index = 0;
	//game.collectibles_counter = 0;
	return (0);
}

int	load_number_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->counter_bar = mlx_xpm_file_to_image(game->mlx, "../textures/counter/counter_bare.xpm", &img_width, &img_height);
	game->number_images[0] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/1.xpm", &img_width, &img_height);
	game->number_images[1] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/2.xpm", &img_width, &img_height);
	game->number_images[2] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/3.xpm", &img_width, &img_height);
	game->number_images[3] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/4.xpm", &img_width, &img_height);
	game->number_images[4] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/5.xpm", &img_width, &img_height);
	game->number_images[5] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/6.xpm", &img_width, &img_height);
	game->number_images[6] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/7.xpm", &img_width, &img_height);
	game->number_images[7] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/8.xpm", &img_width, &img_height);
	game->number_images[8] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/9.xpm", &img_width, &img_height);
	game->number_images[9] = mlx_xpm_file_to_image(game->mlx, "../textures/counter/10.xpm", &img_width, &img_height);
	//game.step_counter = 0;
	//mlx_put_image_to_window(game.mlx, game.mlx_window, game.counter_bar, 0 * TILE_SIZE, 0 * TILE_SIZE);
	return (0);
}

int	load_enemy_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->enemy_frames[0] = mlx_xpm_file_to_image(game->mlx, "../textures/enemy/black_right.xpm", &img_width, &img_height);
	game->enemy_frames[1] = mlx_xpm_file_to_image(game->mlx, "../textures/enemy/black_left.xpm", &img_width, &img_height);
	game->enemy_frame_index = 0;
	game->enemy = game->enemy_frames[0];
	//game.animation_counter = 0;
	return (0);
}

int	load_door_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->door_frames[0] = mlx_xpm_file_to_image(game->mlx, "../textures/door/door.xpm", &img_width, &img_height);
	game->door_frames[1] = mlx_xpm_file_to_image(game->mlx, "../textures/door/door2.xpm", &img_width, &img_height);
	game->door_frames[2] = mlx_xpm_file_to_image(game->mlx, "../textures/door/door3.xpm", &img_width, &img_height);
	game->door_frames[3] = mlx_xpm_file_to_image(game->mlx, "../textures/door/door4.xpm", &img_width, &img_height);
	//game.door_frame_index = 0;
	return (0);
}
