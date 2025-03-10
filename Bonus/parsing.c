#include "game.h"

void free_map_before_exit(t_game *game, int height, char *msg)
{
	ft_free(game->map, height);
	get_next_line(-1);
	ft_printf("Error\n");
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);

}

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

void valid_elm_nbr(t_game *game, int p_count,int e_count, int c_count)
{
	if (p_count > 1)
		free_map_before_exit(game, game->map_height, "Multiple players :(");
	if (p_count == 0)
		free_map_before_exit(game, game->map_height, "No staring position :(");
	if ( e_count > 1)
		free_map_before_exit(game, game->map_height, "Multiple doors :(");
	if ( e_count == 0)
		free_map_before_exit(game, game->map_height, "No exit" );
	if (c_count < 1)
		free_map_before_exit(game, game->map_height, "At least one collectable :)" );

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
					game->map[y][x] != 'P' &&
					game->map[y][x] != 'X')
				free_map_before_exit(game, game->map_height,
						"Invalid character in map" );
			x++;
		}
		y++;
	}
}

int	count_lines(const char *filename)
{
	int	fd;
	int	count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nThere is no file by this name\n");
		exit(1);
	}
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close (fd);
	return (count);
}

void	validate_walls(t_game *game)
{
	int	x;
	int	y;
	char *err_msg;

	x = 0;
	err_msg =  "Map is not surrounded by walls";
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

void	allocate_map(t_game *game, const char *filename)
{
	game->map_height = count_lines(filename);
        if (game->map_height <= 0)
        {
                ft_printf("Error\nheight less than 0\n");
                exit(1);
        }
        game->map = malloc(sizeof(char *) * (game->map_height + 1));
        if (!game->map)
        {
                ft_printf("Error\nMemory Allocation Failed\n");
                exit(1);
        }
}

void	read_and_validate_lines(int fd, t_game *game)
{
	int (i), (width);
	i = 0;
	game->map_width = 0;
	while (i < game->map_height)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
			free_map_before_exit(game, i, "Failed to read map file");
		if (i == 0)
		{
			while (game->map[i][game->map_width] && game->map[i][game->map_width] != '\n')
				game->map_width++;
		}
		else
		{
			width = 0;
			while (game->map[i][width] && game->map[i][width] != '\n')
				width++;
			if (width != game->map_width)
				free_map_before_exit(game, i + 1, "Map is not rectangular");
		}
		i++;
	}
	game->map[i] = NULL;
}

void	read_map(const char *filename, t_game *game)
{
	int	fd;

	allocate_map(game, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCould not open the file\n");
		free(game->map);
		exit(1);
	}
	read_and_validate_lines(fd, game);
	close (fd);
}
