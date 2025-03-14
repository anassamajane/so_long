/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:52:33 by anaamaja          #+#    #+#             */
/*   Updated: 2025/03/13 01:02:46 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

# include "../libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>

# define ESC_KEY 65307
# define TILE_SIZE 64
# define STEP_COUNTER_HEIGHT 80
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
	void	*dead_player;

	void	*door_frames[4];
	int		door_frame_index;

	void	*collectible_frames[2];
	void	*collectibles_img;
	int		collectibles_counter;
	int		collectibles_frame_index;
	int		total_collectibles;
	int		collected;

	void	*enemy;
	void	*enemy_frames[2];
	int		enemy_frame_index;
	int		animation_counter;

	void	*counter_bar;
	void	*number_images[10];
	int		step_counter;

	int		player_x;
	int		player_y;
	int		prev_player_x;
	int		prev_player_y;

	char	**map;
	int		map_width;
	int		map_height;

}			t_game;

/* render_bonus.c */
void		render_map(t_game *game);
void		render_tile(t_game *game, int x, int y);
void		update_changed_tiles(t_game *game);
void		render_steps_counter(t_game *game, int steps);

/* redraw_bonus.c */
void		redraw_all_collectibles(t_game *game);
void		redraw_door(t_game *game);
void		redraw_all_enemies(t_game *game);

/* player_bonus.c */
int			handle_keypress(int keycode, t_game *game);
void		handle_movement(t_game *game, int dx, int dy, void *player_img);
void		handle_death(t_game *game);
void		handle_collectibles(t_game *game);
void		handle_exit(t_game *game);

/* animation.c */
int			animated_game(t_game *game);
void		update_enemy_animation(t_game *game, int *redraw_enemies);
void		update_door_animation(t_game *game, int *rredraw_door);
void		update_collectibles_animation(t_game *game,
				int *redraw_collectibles);

/* load_images_bonus.c */
int			load_player_images(t_game *game);
int			load_collectibles_images(t_game *game);
int			load_number_images(t_game *game);
int			load_enemy_images(t_game *game);
int			load_door_images(t_game *game);

/* init_bonus.c */
int			init_game(t_game *game);
void		count_collectibles(t_game *game);

/* cleanup_bonus.c */
void		cleanup_resources(t_game *game);
void		cleanup_helper(t_game *game);

/* parsing_bonus.c */

void		read_map(const char *file_name, t_game *game);
void		free_map_before_exit(t_game *game, int height, char *msg);

/* parsing_helpers_bonus.c */
void		check_file_extension(const char *filename);
void		validate_map_characters(t_game *game);
void		validate_map_elements(t_game *game);
void		validate_walls(t_game *game);

/* find_path_bonus.c */
void		validate_path(t_game *game);
void		ft_free(char **map_copy, int rows);
#endif
