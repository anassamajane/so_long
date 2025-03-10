#include "game.h"

int	handle_keypress(int keycode, void *param)
{
	t_game	*game = (t_game *)param;

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
	render_steps_counter(game, game->step_counter);
	return (0);
}

void	handle_movement(t_game *game, int dx, int dy, void *player_img)
{
	int	new_x;
	int	new_y;
	char	target;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	target = game->map[new_y][new_x];
	if (target == '1')/*|| (target == 'E' && game->collected != game->total_collectibles))*/
		return ;
	game->player_x = new_x;
	game->player_y = new_y;
	game->current_player = player_img;
	game->step_counter++;
	handle_death(game);
	handle_collectibles(game);
	handle_exit(game);
}

void	handle_death(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == 'X')
	{
		if (game->current_player == game->player_up)
			game->player_y++;
		else if (game->current_player == game->player_down)
			game->player_y--;
		else if (game->current_player == game->player_left)
			game->player_x++;
		else if (game->current_player == game->player_right)
			game->player_x--;
		game->current_player = game->dead_player;
		write (1, "You died!\n", 10);
		render_map(game);
		mlx_do_sync(game->mlx);
		usleep(500000);
		cleanup_resources(game);
		exit (0);
	}
}

void	handle_collectibles(t_game *game)
{
		if (game->map[game->player_y][game->player_x] == 'C')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->collected++;
		if (game->collected == game->total_collectibles)
		{
			if (game->door_frame_index < 3)
				game->door_frame_index++;
			write(1, "Congrats!\n", 10);
		}
	}
}

void	handle_exit(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == 'E' && game->collected == game->total_collectibles)
	{
		write (1, "You Win!\n", 9);
		cleanup_resources(game);
		exit (0);
	}
}
