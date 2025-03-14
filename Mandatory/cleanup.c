/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:53:32 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/10 21:05:35 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	cleanup_resources(t_game *game)
{
	int (i);
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->floor_img);
	mlx_destroy_image(game->mlx, game->player_up);
	mlx_destroy_image(game->mlx, game->player_down);
	mlx_destroy_image(game->mlx, game->player_left);
	mlx_destroy_image(game->mlx, game->player_right);
	mlx_destroy_image(game->mlx, game->door_img);
	mlx_destroy_image(game->mlx, game->collectibles_img);
	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
			free(game->map[i++]);
		free(game->map);
	}
	if (game->mlx_window)
		mlx_destroy_window(game->mlx, game->mlx_window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
}
