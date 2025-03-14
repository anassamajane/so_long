/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:46:18 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/10 21:49:01 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	handle_keypress(int keycode, t_game *game)
{
	game->prev_player_x = game->player_x;
	game->prev_player_y = game->player_y;
	if (keycode == ESC_KEY)
	{
		cleanup_resources(game);
		exit(0);
	}
	if (keycode == KEY_UP)
		handle_movement(game, 0, -1, game->player_up);
	else if (keycode == KEY_DOWN)
		handle_movement(game, 0, 1, game->player_down);
	else if (keycode == KEY_LEFT)
		handle_movement(game, -1, 0, game->player_left);
	else if (keycode == KEY_RIGHT)
		handle_movement(game, 1, 0, game->player_right);
	update_changed_tiles(game);
	return (0);
}

void	handle_movement(t_game *game, int dx, int dy, void *player_img)
{
	int		new_x;
	int		new_y;
	char	target;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	target = game->map[new_y][new_x];
	if (target == '1')
		return ;
	game->player_x = new_x;
	game->player_y = new_y;
	game->current_player = player_img;
	game->step_counter++;
	ft_printf("Movements: %d\n", game->step_counter);
	handle_collectibles(game);
	handle_exit(game);
}

void	handle_collectibles(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == 'C')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->collected++;
	}
}

void	handle_exit(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == 'E' \
			&& game->collected == game->total_collectibles)
	{
		ft_printf("Congratulations! 🎉 ");
		ft_printf("You have completed the game successfully!\n");
		cleanup_resources(game);
		exit (0);
	}
}
