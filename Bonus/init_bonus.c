/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:00:19 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/13 07:27:11 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	init_game(t_game *game)
{
	int (img_width), (img_height);
	game->mlx = mlx_init();
	if (game->map_width <= 5)
		game->mlx_window = mlx_new_window(game->mlx, 6 * TILE_SIZE,
				game->map_height * TILE_SIZE + STEP_COUNTER_HEIGHT,
				"Dragon Ball");
	else
		game->mlx_window = mlx_new_window(game->mlx, game->map_width
				* TILE_SIZE, game->map_height * TILE_SIZE + STEP_COUNTER_HEIGHT,
				"Dragon Ball");
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_floor/80wall.xpm", &img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_floor/black_floor.xpm", &img_width, &img_height);
	if (load_player_images(game) || load_collectibles_images(game)
		|| load_number_images(game) || load_enemy_images(game)
		|| load_door_images(game))
		return (1);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->counter_bar, 0
		* TILE_SIZE, 0 * TILE_SIZE);
	count_collectibles(game);
	return (0);
}

void	count_collectibles(t_game *game)
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
				game->total_collectibles++;
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				game->prev_player_x = x;
				game->prev_player_y = y;
			}
			x++;
		}
		y++;
	}
}
