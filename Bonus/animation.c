/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:33:06 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/11 00:53:43 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	animated_game(t_game *game)
{
	int		redraw_collectibles;
	int		rredraw_door;
	int		redraw_enemies;

	redraw_collectibles = 0;
	rredraw_door = 0;
	redraw_enemies = 0;
	update_enemy_animation(game, &redraw_enemies);
	update_door_animation(game, &rredraw_door);
	update_collectibles_animation(game, &redraw_collectibles);
	if (redraw_enemies)
		redraw_all_enemies(game);
	if (rredraw_door)
		redraw_door(game);
	if (redraw_collectibles)
		redraw_all_collectibles(game);
	usleep(100000);
	return (0);
}

void	update_enemy_animation(t_game *game, int *redraw_enemies)
{
	game->animation_counter++;
	if (game->animation_counter >= 5)
	{
		game->animation_counter = 0;
		if (game->enemy_frame_index < 1)
			game->enemy_frame_index++;
		else
			game->enemy_frame_index = 0;
		game->enemy = game->enemy_frames[game->enemy_frame_index];
		*redraw_enemies = 1;
	}
}

void	update_door_animation(t_game *game, int *rredraw_door)
{
	if (game->collected == game->total_collectibles && \
			game->door_frame_index < 3)
	{
		game->door_frame_index++;
		*rredraw_door = 1;
	}
}

void	update_collectibles_animation(t_game *game, int *redraw_collectibles)
{
	game->collectibles_counter++;
	if (game->collectibles_counter >= 2)
	{
		game->collectibles_counter = 0;
		if (game->collectibles_frame_index == 0)
			game->collectibles_frame_index = 1;
		else
			game->collectibles_frame_index = 0;
	}
	game->collectibles_img = \
		game->collectible_frames[game->collectibles_frame_index];
	*redraw_collectibles = 1;
}
