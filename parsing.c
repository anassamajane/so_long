#include "game.h"


int	count_lines(const char *filename)
{
	int	fd;
	int	count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close (fd);
	return (count);
}

void	read_map(const char *filename, t_game *game)
{
	int	fd;
	int	i;
	int	width;

	game->map_height = count_lines(filename);
	if (game->map_height <= 0)
	{
		printf("Error: height less than 0\n");
		return ;
	}
	game->mapp = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->mapp)
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
		game->mapp[i] = get_next_line(fd);
		if (!game->mapp[i])
		{
			printf("Error: Failed to read map file\n");
			return ;
		}
		if (i == 0)
		{
			while (game->mapp[i][game->map_width] && game->mapp[i][game->map_width] != '\n')
				game->map_width++;
		}
		else
		{
			width = 0;
			while (game->mapp[i][width] && game->mapp[i][width] != '\n')
				width++;
			if (width != game->map_width)
			{
				printf("Error: Different row width in the map\n");
				return ;
			}
		}
		i++;
	}
	game->mapp[i] = NULL;
	close(fd);
}
