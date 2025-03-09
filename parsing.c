#include "game.h"

void	check_file_extension(const char *filename)
{
	int	len;

	len = strlen(filename);
	if (len < 5 || strcmp(filename + len - 4, ".ber") != 0)
	{
		printf("Error: Invalid file extension. Use a .ber file\n");
		exit(1);
	}
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
	{
		printf("Error: Invalid map element (P=%d, E=%d, C=%d)\n", player_count, exit_count, collectibles_count);
		exit (1);
	}
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
			if (game->map[y][x] != '0' && game->map[y][x] != '1' && game->map[y][x] != 'C' && game->map[y][x] != 'E' && game->map[y][x] != 'P' && game->map[y][x] != 'X')
			{
				printf("Error: Invalid character in map\n");
				exit(1);
			}
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
		printf("Error: there is no file by this name\n");
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

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
		{
			printf("Error: Map is not surrounded by walls\n");
			exit(1);
		}
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
		{
			printf("Error: Map is nor surrounded by walls\n");
			exit(1);
		}
		y++;
	}
}


void	allocate_map(t_game *game, const char *filename)
{
	game->map_height = count_lines(filename);
        if (game->map_height <= 0)
        {
                printf("Error: height less than 0\n");
                exit(1);
        }
        game->map = malloc(sizeof(char *) * (game->map_height + 1));
        if (!game->map)
        {
                printf("Error: Memory Allocation Failed\n");
                exit(1);
        }
}

void	read_and_validate_lines(int fd, t_game *game)
{
	int	i;
	int	width;

	i = 0;
        game->map_width = 0;
        while (i < game->map_height)
        {
                game->map[i] = get_next_line(fd);
                if (!game->map[i])
                {
                        printf("Error: Failed to read map file\n");
                        exit(1);
                }
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
                        {
                                printf("Error: Different row width in the map\n");
                                exit(1);
                        }
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
		printf("Error: Could not open the file\n");
		free(game->map);
		exit(1);
	}
	read_and_validate_lines(fd, game);
	close (fd);
}
/*void	read_map(const char *filename, t_game *game)
{
	int	fd;
	int	i;
	int	width;

	game->map_hrintf("Error: Failed eight = count_lines(filename);
	if (game->map_height <= 0)
	{
		printf("Error: height less than 0\n");
		return ;
	}
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
	{
		printf("Error: Memory Allocation Failed\n");
		return ;
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Could Not Open The File\n");
		free(game->map);
		return ;
	}
	i = 0;
	game->map_width = 0;
	while (i < game->map_height)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
		{
			printf("Error: Failed to read map file\n");
			return ;
		}
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
			{
				printf("Error: Different row width in the map\n");
				return ;
			}
		}
		i++;
	}
	game->map[i] = NULL;
	close(fd);
}*/
