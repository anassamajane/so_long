#include "game.h"

void	cleanup_resources(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->floor_img);
	mlx_destroy_image(game->mlx, game->player_up);
	mlx_destroy_image(game->mlx, game->player_down);
	mlx_destroy_image(game->mlx, game->player_left);
	mlx_destroy_image(game->mlx, game->player_right);
	mlx_destroy_image(game->mlx, game->dead_player);
	mlx_destroy_image(game->mlx, game->door_img);
	mlx_destroy_image(game->mlx, game->collectibles_img);
	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	if (game->mlx_window)
                mlx_destroy_window(game->mlx, game->mlx_window);
        if (game->mlx)
                mlx_destroy_display(game->mlx);
        if (game->mlx)
                free(game->mlx);
}
