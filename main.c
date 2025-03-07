#include "game.h"

int	main()
{
	t_game	game;

	if (init_game(&game))
		return (1);

	read_map("maps/map1.ber", &game);
	printf("Map height: %d\n", game.map_height);
	printf("Map Width: %d\n", game.map_width);

	for (int i = 0; i < game.map_height; i++)
		printf("%s", game.map[i]);

	init_map(&game);
	render_map(&game);
	mlx_key_hook(game.mlx_window, handle_keypress, &game);
	mlx_loop_hook(game.mlx, animated_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
