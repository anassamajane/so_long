#include "game.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error: Please provide a map file\n");
		return (1);
	}
	check_file_extension(av[1]);
	read_map(av[1], &game);
	validate_walls(&game);
	validate_map_characters(&game);
	validate_map_elements(&game);
	validate_path(&game);

	printf("Map height: %d\n", game.map_height);
	printf("Map Width: %d\n", game.map_width);
	//for (int i = 0; i < game.map_height; i++)
	//	printf("%s", game.map[i]);
	//return (0);	
	if (init_game(&game))
		return (1);
	render_map(&game);
	mlx_key_hook(game.mlx_window, handle_keypress, &game);
	mlx_loop_hook(game.mlx, animated_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
