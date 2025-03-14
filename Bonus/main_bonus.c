/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:14:04 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/13 07:28:32 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	handle_window_close(t_game *game)
{
	cleanup_resources(game);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_printf("Error: Please provide a map file\n");
		return (1);
	}
	ft_bzero(&game, sizeof(game));
	check_file_extension(av[1]);
	read_map(av[1], &game);
	validate_walls(&game);
	validate_map_characters(&game);
	validate_map_elements(&game);
	validate_path(&game);
	if (init_game(&game))
		return (1);
	render_map(&game);
	mlx_key_hook(game.mlx_window, handle_keypress, &game);
	mlx_loop_hook(game.mlx, animated_game, &game);
	mlx_hook(game.mlx_window, 17, 0, handle_window_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
