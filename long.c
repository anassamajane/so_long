#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

#define ESC_KEY 65307
#define TILE_SIZE 64
#define MAP_HEIGHT 10
#define MAP_WIDTH 10


typedef struct	s_game
{
	void	*mlx;
	void	*mlx_window;
	void	*wall_img;
	void	*floor_img;
	void	*player_img;
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

	int	new_x = game->player_x;
	int	new_y = game->player_y;

	if (keycode == 65361)
		new_x--;
	else if (keycode == 65363)
		new_x++;
	else if (keycode == 65362)
		new_y--;
	else if (keycode == 65364)
		new_y++;

	if (game->map[new_y][new_x] != '1')
	{
		game->player_x = new_x;
		game->player_y = new_y;
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
			else
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->player_img, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}
int	main(void)
{
	t_game	game;
	void	*image;
	int		img_width;
	int		img_height;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Map");

	game.wall_img = mlx_xpm_file_to_image(game.mlx, "3.xpm", &img_width, &img_height);
	game.floor_img = mlx_xpm_file_to_image(game.mlx, "black_floor.xpm", &img_width, &img_height);
	if (!game.wall_img || !game.floor_img)
	{
		write(2, "Error\n", 6);
		return (1);
	}

	game.player_img = mlx_xpm_file_to_image(game.mlx, "1.xpm", &img_width, &img_height);
	if (!game.player_img)
	{
		write(2, "Error_player\n", 13);
		return (1);
	}
	char temp_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
		"1111111111",
		"10P0000001",
		"1000000001",
		"1010000101",
		"1010110101",
		"1010000101",
		"1011111101",
		"1000000001",
		"1000000001",
		"1111111111"
	};

	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			game.map[i][j] = temp_map[i][j];

	for (int y = 0; y < MAP_WIDTH; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (game.map[y][x] == 'P')
			{
				game.player_x = x;
				game.player_y = y;
			}
		}
	}

	render_map(&game);
	mlx_key_hook(game.mlx_window, handle_keypress, &game);
	mlx_loop(game.mlx);
}
