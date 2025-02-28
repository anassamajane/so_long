#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define ESC_KEY 65307
#define TILE_SIZE 64
#define MAP_HEIGHT 10
#define MAP_WIDTH 36
#define STEP_COUNTER_HEIGHT 80
#define WINDOW_HEIGHT (MAP_HEIGHT * TILE_SIZE + STEP_COUNTER_HEIGHT)
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
	void	*current_player;
	void	*dead_player;

	void	*door_frames[4];
	int	door_frame_index;

	void	*collectible_frames[2];
	void	*collectibles_img;
	int	collectibles_counter;
	int	collectibles_frame_index;
	int	total_collectibles;
	int	collected;

	void	*enemy;
	void	*enemy_frames[2];
	int	enemy_frame_index;
	int	animation_counter;

	void	*counter_bar;
	void	*number_images[10];
	int	step_counter;

	int	player_x;
	int	player_y;
	int	prev_player_x;
	int	prev_player_y;
	char	map[MAP_HEIGHT][MAP_WIDTH + 1];

}	t_game;

void    render_map(t_game *game);
void	handle_death(t_game *game);
void    rander_steps_counter(t_game *game, int steps);
void    update_changed_tiles(t_game *game);
void    redraw_all_collectibles(t_game *game);
void    redraw_door(t_game *game);
void    redraw_all_enemies(t_game *game);
void	cleanup_resources(t_game *game);

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
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->wall_img, x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->collectibles_img, x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->door_frames[game->door_frame_index], x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
			else if (game->map[y][x] == 'X')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->enemy, x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
			else
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->floor_img, x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->current_player, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE + STEP_COUNTER_HEIGHT);
}


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


	if (keycode == KEY_UP && game->map[game->player_y - 1][game->player_x] != '1' && (game->map[game->player_y - 1][game->player_x] != 'E' || game->collected == game->total_collectibles))
	{
		game->player_y--;
		game->current_player = game->player_up;
		handle_death(game);
		game->step_counter++;
	}

	else if (keycode == KEY_DOWN && game->map[game->player_y + 1][game->player_x] != '1' && (game->map[game->player_y + 1][game->player_x] != 'E' || game->collected == game->total_collectibles))
        {
		game->player_y++;
		game->current_player = game->player_down;
		handle_death(game);
		game->step_counter++;
        }

	else if (keycode == KEY_LEFT && game->map[game->player_y][game->player_x - 1] != '1' && (game->map[game->player_y][game->player_x - 1] != 'E' || game->collected == game->total_collectibles))
        {
                game->player_x--;
                game->current_player = game->player_left;
		handle_death(game);
		game->step_counter++;
        }

	else if (keycode == KEY_RIGHT && game->map[game->player_y][game->player_x + 1] != '1' && (game->map[game->player_y][game->player_x + 1] != 'E' || game->collected == game->total_collectibles))
        {
                game->player_x++;
                game->current_player = game->player_right;
		handle_death(game);
		game->step_counter++;
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

	if (game->map[game->player_y][game->player_x] == 'E' && game->collected == game->total_collectibles)
	{
		write (1, "You Win!\n", 9);
		cleanup_resources(game);
		exit (0);
	}
	update_changed_tiles(game);
	rander_steps_counter(game, game->step_counter);
	return (0);
}

void	update_changed_tiles(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->floor_img, game->prev_player_x * TILE_SIZE, game->prev_player_y * TILE_SIZE + STEP_COUNTER_HEIGHT);
	if (game->map[game->prev_player_y][game->prev_player_x] == '1')
		mlx_put_image_to_window(game->mlx, game->mlx_window, game->wall_img, game->prev_player_x * TILE_SIZE, game->prev_player_y * TILE_SIZE + STEP_COUNTER_HEIGHT);
	else if (game->map[game->prev_player_y][game->prev_player_x] == 'C')
		mlx_put_image_to_window(game->mlx, game->mlx_window, game->collectibles_img, game->prev_player_x * TILE_SIZE, game->prev_player_y * TILE_SIZE + STEP_COUNTER_HEIGHT);
	else if (game->map[game->prev_player_y][game->prev_player_x] == 'E')
		mlx_put_image_to_window(game->mlx, game->mlx_window, game->door_frames[game->door_frame_index], game->prev_player_x * TILE_SIZE, game->prev_player_y * TILE_SIZE + STEP_COUNTER_HEIGHT);
	else if (game->map[game->prev_player_y][game->prev_player_x] == 'X')
		mlx_put_image_to_window(game->mlx, game->mlx_window, game->enemy, game->prev_player_x * TILE_SIZE, game->prev_player_y * TILE_SIZE + STEP_COUNTER_HEIGHT);

	mlx_put_image_to_window(game->mlx, game->mlx_window, game->current_player, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE + STEP_COUNTER_HEIGHT);
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


int	animated_game(void *param)
{
	t_game	*game = (t_game *)param;
	int	redraw_collectibles = 0;
	int	rredraw_door = 0;
	int	redraw_enemies = 0;

	game->animation_counter++;
	if (game->animation_counter >= 5)
	{
		game->animation_counter = 0;
		if (game->enemy_frame_index < 1)
			game->enemy_frame_index++;
		else
			game->enemy_frame_index = 0;
		game->enemy = game->enemy_frames[game->enemy_frame_index];
		redraw_enemies = 1;
	}

	if (game->collected == game->total_collectibles && game->door_frame_index < 3)
        {
                game->door_frame_index++;
		rredraw_door = 1;
        }

	game->collectibles_counter++;
	if (game->collectibles_counter >= 2)
	{
		game->collectibles_counter = 0;
		if (game->collectibles_frame_index == 0)
			game->collectibles_frame_index = 1;
		else
			game->collectibles_frame_index = 0;
		game->collectibles_img = game->collectible_frames[game->collectibles_frame_index];
		redraw_collectibles = 1;
	}

	if (redraw_enemies)
		redraw_all_enemies(game);
	if (rredraw_door)
		redraw_door(game);
	if (redraw_collectibles)
		redraw_all_collectibles(game);
	usleep(100000);
	return (0);
}

void	redraw_all_collectibles(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_window, game->collectibles_img, x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
			x++;
		}
		y++;
	}
}

void	redraw_door(t_game *game)
{
	int     x;
        int     y;

        y = 0;
        while (y < MAP_HEIGHT)
        {
                x = 0;
                while (x < MAP_WIDTH)
                {
                        if (game->map[y][x] == 'E')
                                mlx_put_image_to_window(game->mlx, game->mlx_window, game->door_frames[game->door_frame_index], x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
                        x++;
                }
                y++;
        }
}

void	redraw_all_enemies(t_game *game)
{
	 int     x;
        int     y;

        y = 0;
        while (y < MAP_HEIGHT)
        {
                x = 0;
                while (x < MAP_WIDTH)
                {
                        if (game->map[y][x] == 'X')
                                mlx_put_image_to_window(game->mlx, game->mlx_window, game->enemy, x * TILE_SIZE, y * TILE_SIZE + STEP_COUNTER_HEIGHT);
                        x++;
                }
                y++;
        }
}

void	cleanup_resources(t_game *game)
{
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->floor_img);
	mlx_destroy_image(game->mlx, game->player_up);
	mlx_destroy_image(game->mlx, game->player_down);
	mlx_destroy_image(game->mlx, game->player_left);
	mlx_destroy_image(game->mlx, game->player_right);
	mlx_destroy_image(game->mlx, game->dead_player);
	for (int i = 0; i < 4; i++)
		mlx_destroy_image(game->mlx, game->door_frames[i]);
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(game->mlx, game->collectible_frames[i]);
	for (int i = 0; i < 2; i++)
		mlx_destroy_image(game->mlx, game->enemy_frames[i]);
	for (int i = 0; i < 10; i++)
		mlx_destroy_image(game->mlx, game->number_images[i]);
	if (game->counter_bar)
		mlx_destroy_image(game->mlx, game->counter_bar);
	if (game->mlx_window)
		mlx_destroy_window(game->mlx, game->mlx_window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
}

void    rander_steps_counter(t_game *game, int steps)
{
        mlx_put_image_to_window(game->mlx, game->mlx_window, game->number_images[(steps / 1000) % 10], 176, 10);
        mlx_put_image_to_window(game->mlx, game->mlx_window, game->number_images[(steps / 100) % 10], 219, 10);
        mlx_put_image_to_window(game->mlx, game->mlx_window, game->number_images[(steps / 10) % 10], 261, 10);
        mlx_put_image_to_window(game->mlx, game->mlx_window, game->number_images[steps % 10], 304 , 10);
}

int	main(void)
{
	t_game	game;
	int		img_width;
	int		img_height;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx, MAP_WIDTH * TILE_SIZE, WINDOW_HEIGHT, "Map");

	game.wall_img = mlx_xpm_file_to_image(game.mlx, "80wall.xpm", &img_width, &img_height);
	game.floor_img = mlx_xpm_file_to_image(game.mlx, "black_floor.xpm", &img_width, &img_height);
	if (!game.wall_img || !game.floor_img)
	{
		write(2, "Error\n", 6);
		return (1);
	}

	game.player_up = mlx_xpm_file_to_image(game.mlx, "goku_up.xpm", &img_width, &img_height);
	game.player_down = mlx_xpm_file_to_image(game.mlx, "goku_down.xpm", &img_width, &img_height);
	game.player_left = mlx_xpm_file_to_image(game.mlx, "goku_left.xpm", &img_width, &img_height);
	game.player_right = mlx_xpm_file_to_image(game.mlx, "goku_right.xpm", &img_width, &img_height);
	game.dead_player = mlx_xpm_file_to_image(game.mlx, "dead_goku.xpm", &img_width, &img_height);
	game.current_player = game.player_right;
	game.prev_player_x = game.player_x;
	game.prev_player_y = game.player_y;

	game.collectible_frames[0] = mlx_xpm_file_to_image(game.mlx, "Dragonball_up1.xpm", &img_width, &img_height);
	game.collectible_frames[1] = mlx_xpm_file_to_image(game.mlx, "Dragonball_down.xpm", &img_width, &img_height);
	game.collectibles_img = game.collectible_frames[0];
	game.collectibles_frame_index = 0;
	game.collectibles_counter = 0;


	game.counter_bar = mlx_xpm_file_to_image(game.mlx, "counter_bare.xpm", &img_width, &img_height);
	game.number_images[0] = mlx_xpm_file_to_image(game.mlx, "1.xpm", &img_width, &img_height);
	game.number_images[1] = mlx_xpm_file_to_image(game.mlx, "2.xpm", &img_width, &img_height);
	game.number_images[2] = mlx_xpm_file_to_image(game.mlx, "3.xpm", &img_width, &img_height);
	game.number_images[3] = mlx_xpm_file_to_image(game.mlx, "4.xpm", &img_width, &img_height);
	game.number_images[4] = mlx_xpm_file_to_image(game.mlx, "5.xpm", &img_width, &img_height);
	game.number_images[5] = mlx_xpm_file_to_image(game.mlx, "6.xpm", &img_width, &img_height);
	game.number_images[6] = mlx_xpm_file_to_image(game.mlx, "7.xpm", &img_width, &img_height);
	game.number_images[7] = mlx_xpm_file_to_image(game.mlx, "8.xpm", &img_width, &img_height);
	game.number_images[8] = mlx_xpm_file_to_image(game.mlx, "9.xpm", &img_width, &img_height);
	game.number_images[9] = mlx_xpm_file_to_image(game.mlx, "10.xpm", &img_width, &img_height);
	game.step_counter = 0;
	mlx_put_image_to_window(game.mlx, game.mlx_window, game.counter_bar, 0 * TILE_SIZE, 0 * TILE_SIZE);

	game.enemy_frames[0] = mlx_xpm_file_to_image(game.mlx, "black_right.xpm", &img_width, &img_height);
	game.enemy_frames[1] = mlx_xpm_file_to_image(game.mlx, "black_left.xpm", &img_width, &img_height);
	game.enemy_frame_index = 0;
	game.enemy = game.enemy_frames[0];
	game.animation_counter = 0;

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
    		"111111111111111111111111111111111111",
    		"1E00000000X0000C00000C00000000000001",
    		"101001010010000010100100000001010101",
    		"101001001010101000100100000001010101",
    		"1P000X000C00C0000000000000000X000C01",
    		"101001010010000010100100000001010101",
    		"101001001010101000100100000001010101",
    		"1C00000000X0000C00000C00000000000C01",
    		"10000000000000000X00000000000X000001",
    		"111111111111111111111111111111111111"
	};


	/*char temp_map[MAP_HEIGHT][MAP_WIDTH + 1] = { 58/168
		"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
		"100000000000000000000000000000000000001001100000000000000000000000000000000000001001100000000000000000000000000000000000001001100000000000000000000000000000000000001001",
		"10P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C001",
		"10100C01000000111111111100000000010000100110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C001",
		"1010110100000000001100000000000010C00100111010110100000000001100000000000010C00100111010110100000000001100000000000010C00100111010110100000000001100000000000010C0010011",
		"1010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC001000000000100001001",
		"10001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K001001",
		"10000010000000000000000000000000010000100110001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K001001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"100000000000000000000000000000000000001001100000000000000000000000000000000000001001100000000000000000000000000000000000001001100000000000000000000000000000000000001001",
		"10P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C001",
		"10100C01000000111111111100000000010000100110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C001",
		"1010110100000000001100000000000010C00100111010110100000000001100000000000010C00100111010110100000000001100000000000010C00100111010110100000000001100000000000010C0010011",
		"1010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC001000000000100001001",
		"10001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K001001",
		"10000010000000000000000000000000010000100110001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K001001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"100000000000000000000000000000000000001001100000000000000000000000000000000000001001100000000000000000000000000000000000001001100000000000000000000000000000000000001001",
		"10P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C001",
		"10100C01000000111111111100000000010000100110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C00110P0000C000000000000000000000000000000C001",
		"1010110100000000001100000000000010C00100111010110100000000001100000000000010C00100111010110100000000001100000000000010C00100111010110100000000001100000000000010C0010011",
		"1010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC0010000000001000010011010C0K00000001000CCC001000000000100001001",
		"10001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K001001",
		"10000010000000000000000000000000010000100110001110000000111111111100000000010K00100110001110000000111111111100000000010K00100110001110000000111111111100000000010K001001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"1E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C000011E000K0000C00000000CCCCCC000000K0000C00001",
		"111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
	};*/

	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
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
	mlx_loop_hook(game.mlx, animated_game, &game);
	mlx_loop(game.mlx);
}

