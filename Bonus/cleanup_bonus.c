/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:28:07 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/11 00:53:52 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void	cleanup_helper(t_game *game)
{
	int (i), (j), (k);
	i = 0;
	while (i < 4)
		mlx_destroy_image(game->mlx, game->door_frames[i++]);
	j = 0;
	while (j < 10)
		mlx_destroy_image(game->mlx, game->number_images[j++]);
	if (game->map)
	{
		k = 0;
		while (k < game->map_height)
		{
			free(game->map[k]);
			k++;
		}
		free(game->map);
	}
}

void	cleanup_resources(t_game *game)
{
	if (!game->mlx)
		return ;
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->floor_img);
	mlx_destroy_image(game->mlx, game->player_up);
	mlx_destroy_image(game->mlx, game->player_down);
	mlx_destroy_image(game->mlx, game->player_left);
	mlx_destroy_image(game->mlx, game->player_right);
	mlx_destroy_image(game->mlx, game->dead_player);
	mlx_destroy_image(game->mlx, game->collectible_frames[0]);
	mlx_destroy_image(game->mlx, game->collectible_frames[1]);
	mlx_destroy_image(game->mlx, game->enemy_frames[0]);
	mlx_destroy_image(game->mlx, game->enemy_frames[1]);
	cleanup_helper(game);
	if (game->counter_bar)
		mlx_destroy_image(game->mlx, game->counter_bar);
	if (game->mlx_window)
		mlx_destroy_window(game->mlx, game->mlx_window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
