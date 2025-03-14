/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:32:32 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/11 00:56:10 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->current_player,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE
		+ STEP_COUNTER_HEIGHT);
}

void	render_tile(t_game *game, int x, int y)
{
	void	*img;

	if (game->map[y][x] == '1')
		img = game->wall_img;
	else if (game->map[y][x] == 'C')
		img = game->collectibles_img;
	else if (game->map[y][x] == 'E')
		img = game->door_frames[game->door_frame_index];
	else if (game->map[y][x] == 'X')
		img = game->enemy;
	else
		img = game->floor_img;
	mlx_put_image_to_window(game->mlx, game->mlx_window, img, x * TILE_SIZE, y
		* TILE_SIZE + STEP_COUNTER_HEIGHT);
}

void	update_changed_tiles(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->floor_img,
		game->prev_player_x * TILE_SIZE, game->prev_player_y * TILE_SIZE
		+ STEP_COUNTER_HEIGHT);
	render_tile(game, game->prev_player_x, game->prev_player_y);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->current_player,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE
		+ STEP_COUNTER_HEIGHT);
}

void	render_steps_counter(t_game *game, int steps)
{
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->number_images[(steps / 1000) % 10], 176, 10);
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->number_images[(steps / 100) % 10], 219, 10);
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->number_images[(steps / 10) % 10], 261, 10);
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->number_images[steps % 10], 304, 10);
}
