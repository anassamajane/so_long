/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:55:05 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/10 21:55:07 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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
	mlx_put_image_to_window(game->mlx, game->mlx_window, \
			game->current_player, game->player_x * TILE_SIZE, \
			game->player_y * TILE_SIZE);
}

void	render_tile(t_game *game, int x, int y)
{
	void	*img;

	if (game->map[y][x] == '1')
		img = game->wall_img;
	else if (game->map[y][x] == 'C')
		img = game->collectibles_img;
	else if (game->map[y][x] == 'E')
		img = game->door_img;
	else
		img = game->floor_img;
	mlx_put_image_to_window(game->mlx, game->mlx_window, \
			img, x * TILE_SIZE, y * TILE_SIZE);
}

void	update_changed_tiles(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_window, \
			game->floor_img, game->prev_player_x * TILE_SIZE, \
			game->prev_player_y * TILE_SIZE);
	render_tile(game, game->prev_player_x, game->prev_player_y);
	mlx_put_image_to_window(game->mlx, game->mlx_window, \
			game->current_player, game->player_x * TILE_SIZE, \
			game->player_y * TILE_SIZE);
}
