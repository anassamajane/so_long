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
	return (0);
}

int	load_collectibles_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->collectibles_img = mlx_xpm_file_to_image(game->mlx, "../textures/collectibles/Dragonball_up1.xpm", &img_width, &img_height);
	return (0);
}

int	load_door_images(t_game *game)
{
	int	img_width;
	int	img_height;
	
	game->door_img = mlx_xpm_file_to_image(game->mlx, "../textures/door/door.xpm", &img_width, &img_height);
	return (0);
}
