/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:31:37 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/11 00:55:51 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

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
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->collectibles_img, x * TILE_SIZE, y * TILE_SIZE
					+ STEP_COUNTER_HEIGHT);
			x++;
		}
		y++;
	}
}

void	redraw_door(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->door_frames[game->door_frame_index], x * TILE_SIZE, y
					* TILE_SIZE + STEP_COUNTER_HEIGHT);
			x++;
		}
		y++;
	}
}

void	redraw_all_enemies(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'X')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->enemy, x * TILE_SIZE, y * TILE_SIZE
					+ STEP_COUNTER_HEIGHT);
			x++;
		}
		y++;
	}
}
