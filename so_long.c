#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

#define ESC_KEY 65307
#define TILE_SIZE 64
#define MAP_HEIGHT 10
#define MAP_WIDTH 10
#define KEY_UP 65362
#define	KEY_DOWN 65364
#define	KEY_LEFT 65361
#define KEY_RIGHT 65363


typedef struct	s_game
{
	void	*mlx;
	void	*mlx_window;
	void	*wall_img;
	void	*floor_img;
	void	*player_up;
	void	*player_down;
	void	*player_left;
	void	*player_right;
	void	*player_hit_ground;
	void	*current_player;
	void	*door_frames[4];
	int	door_frame_index;
	void	*collectible_img;
	int	total_collectibles;
	int	collected;
	int	player_x;
	int	player_y;
	char	map[MAP_HEIGHT][MAP_WIDTH + 1];
}	t_game;

void    render_map(t_game *game);

int	handle_keypress(int keycode, void *param)
{
	t_game	*game = (t_game *)param;

	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(game->mlx, game->mlx_window);
		exit(0);
	}


	if (keycode == KEY_UP && game->map[game->player_y - 1][game->player_x] != '1')
	{
		game->player_y--;
		game->current_player = game->player_up;
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

	else if (keycode == KEY_DOWN)
        {
		if (game->map[game->player_y + 1][game->player_x] == '1')
			game->current_player = game->player_hit_ground;
		else
		{
			game->player_y++;
			game->current_player = game->player_down;
		}
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
	else if (keycode == KEY_LEFT && game->map[game->player_y][game->player_x - 1] != '1')
        {
                game->player_x--;
                game->current_player = game->player_left;
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
	else if (keycode == KEY_RIGHT && game->map[game->player_y][game->player_x + 1] != '1')
        {
                game->player_x++;
                game->current_player = game->player_right;
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

	render_map(game);
	return (0);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->door_frames[game->door_frame_index], x * TILE_SIZE, y * TILE_SIZE);
			else
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->current_player, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}

int	animated_door(void *param)
{
	t_game	*game = (t_game *)param;

	if (game->collected == game->total_collectibles && game->door_frame_index < 3)
	{
		usleep (200000);
		game->door_frame_index++;
		render_map(game);
	}
	return (0);
}

int	main(void)
{
	t_game	game;
	void	*image;
	int		img_width;
	int		img_height;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Map");

	game.wall_img = mlx_xpm_file_to_image(game.mlx, "wally.xpm", &img_width, &img_height);
	game.floor_img = mlx_xpm_file_to_image(game.mlx, "black_floor.xpm", &img_width, &img_height);
	if (!game.wall_img || !game.floor_img)
	{
		write(2, "Error\n", 6);
		return (1);
	}

	game.player_up = mlx_xpm_file_to_image(game.mlx, "goku4.xpm", &img_width, &img_height);
	game.player_down = mlx_xpm_file_to_image(game.mlx, "goku3.xpm", &img_width, &img_height);
	game.player_left = mlx_xpm_file_to_image(game.mlx, "goku_left.xpm", &img_width, &img_height);
	game.player_right = mlx_xpm_file_to_image(game.mlx, "goku_right.xpm", &img_width, &img_height);
	game.player_hit_ground = mlx_xpm_file_to_image(game.mlx, "goku5.xpm", &img_width, &img_height);
	game.current_player = game.player_right;
	game.collectible_img = mlx_xpm_file_to_image(game.mlx, "collect.xpm", &img_width, &img_height);
	
	game.door_frames[0] = mlx_xpm_file_to_image(game.mlx, "door.xpm", &img_width, &img_height);
	game.door_frames[1] = mlx_xpm_file_to_image(game.mlx, "door2.xpm", &img_width, &img_height);
	game.door_frames[2] = mlx_xpm_file_to_image(game.mlx, "door3.xpm", &img_width, &img_height);
	game.door_frames[3] = mlx_xpm_file_to_image(game.mlx, "door4.xpm", &img_width, &img_height);
	game.door_frame_index = 0;
	if (!game.player_up)
	{
		write(2, "Error_player_up\n", 16);
		return (1);
	}
	if (!game.player_down)
        {
                write(2, "Error_player_down\n", 18);
                return (1);
        }
	if (!game.player_left)
        {
                write(2, "Error_player_left\n", 18);
                return (1);
        }
	if (!game.player_right)
        {
                write(2, "Error_player_right\n", 19);
                return (1);
        }
	if (!game.current_player)
        {
                write(2, "Error_current_player\n", 21);
                return (1);
        }

	char temp_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
		"1111111111",
		"1C00PC0001",
		"1000110001",
		"100C00C001",
		"1010110111",
		"1C10E00001",
		"1011111101",
		"100000C101",
		"100C000101",
		"1111111111"
	};

	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			game.map[i][j] = temp_map[i][j];

	game.total_collectibles = 0;
	game.collected = 0;
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (game.map[y][x] == 'C')
				game.total_collectibles++;
			if (game.map[y][x] == 'P')
			{
				game.player_x = x;
				game.player_y = y;
			}
		}
	}

	render_map(&game);
	mlx_key_hook(game.mlx_window, handle_keypress, &game);
	mlx_loop_hook(game.mlx, animated_door, &game);
	mlx_loop(game.mlx);
}
