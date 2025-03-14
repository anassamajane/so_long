/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:18:37 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/12 22:13:20 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	init_game(t_game *game)
{
	int	img_width;
	int	img_height;

	game->mlx = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx, game->map_width * TILE_SIZE \
			, game->map_height * TILE_SIZE, "Dragon Ball");
	game->wall_img = mlx_xpm_file_to_image(game->mlx, \
			"textures/wall_floor/80wall.xpm", &img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, \
			"textures/wall_floor/black_floor.xpm", &img_width, &img_height);
	if (load_player_images(game) || load_collectibles_images(game) \
			|| load_door_images(game))
		return (1);
	game->collected = 0;
	game->step_counter = 0;
	game->collectibles_counter = 0;
	count_collectibles(game);
	return (0);
}

void	count_collectibles(t_game *game)
{
	int	x;
	int	y;

	game->total_collectibles = 0;
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
