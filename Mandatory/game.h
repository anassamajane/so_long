/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:30:18 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/13 01:05:36 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>

# define ESC_KEY 65307
# define TILE_SIZE 64
# define KEY_UP 'w'
# define KEY_DOWN 's'
# define KEY_LEFT 'a'
# define KEY_RIGHT 'd'

typedef struct s_game
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

	void	*door_img;

	void	*collectibles_img;
	int		collectibles_counter;
	int		total_collectibles;
	int		collected;

	int		step_counter;

	int		player_x;
	int		player_y;
	int		prev_player_x;
	int		prev_player_y;

	char	**map;
	int		map_width;
	int		map_height;

}			t_game;

/* render.c */
void		render_map(t_game *game);
void		render_tile(t_game *game, int x, int y);
void		update_changed_tiles(t_game *game);

/* player.c */
int			handle_keypress(int keycode, t_game *game);
void		handle_movement(t_game *game, int dx, int dy, void *player_img);
void		handle_collectibles(t_game *game);
void		handle_exit(t_game *game);

/* load_images.c */
int			load_player_images(t_game *game);
int			load_collectibles_images(t_game *game);
int			load_door_images(t_game *game);

/* init.c */
int			init_game(t_game *game);
void		count_collectibles(t_game *game);

/* cleanup.c */
void		cleanup_resources(t_game *game);

/* parsing.c */
void		free_map_before_exit(t_game *game, int height, char *msg);
void		read_map(const char *file_name, t_game *game);

/* parsing_helpers.c */
void		check_file_extension(const char *filename);
void		validate_map_characters(t_game *game);
void		validate_map_elements(t_game *game);
void		validate_walls(t_game *game);

/* find_path.c */
void		validate_path(t_game *game);
void		ft_free(char **map_copy, int rows);
#endif
