/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:27:01 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/10 21:44:21 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	check_file_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error\nInvalid file extension. Use a .ber file\n");
		exit(1);
	}
}

void	valid_elm_nbr(t_game *game, int p_count, int e_count, int c_count)
{
	if (p_count > 1)
		free_map_before_exit(game, game->map_height, "Multiple players :(");
	if (p_count == 0)
		free_map_before_exit(game, game->map_height, "No staring position :(");
	if (e_count > 1)
		free_map_before_exit(game, game->map_height, "Multiple doors :(");
	if (e_count == 0)
		free_map_before_exit(game, game->map_height, "No exit" );
	if (c_count < 1)
		free_map_before_exit(game, game->map_height, \
				"At least one collectable :)" );
}

void	validate_map_elements(t_game *game)
{
	int (x), (y), (player_count), (exit_count), (collectibles_count);
	player_count = 0;
	exit_count = 0;
	collectibles_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
				player_count++;
			else if (game->map[y][x] == 'E')
				exit_count++;
			else if (game->map[y][x] == 'C')
				collectibles_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1 || exit_count != 1 || collectibles_count < 1)
		valid_elm_nbr(game, player_count, exit_count, collectibles_count);
}

void	validate_map_characters(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1' &&
					game->map[y][x] != 'C' &&
					game->map[y][x] != 'E' &&
					game->map[y][x] != 'P')
				free_map_before_exit(game, game->map_height, \
						"Invalid character in map" );
			x++;
		}
		y++;
	}
}

void	validate_walls(t_game *game)
{
	int		x;
	int		y;
	char	*err_msg;

	x = 0;
	err_msg = "Map is not surrounded by walls";
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
			free_map_before_exit(game, game->map_height, err_msg);
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
			free_map_before_exit(game, game->map_height, err_msg);
		y++;
	}
}
