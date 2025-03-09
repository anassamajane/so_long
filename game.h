#ifndef GAME_H
# define GAME_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

# define ESC_KEY 65307
# define TILE_SIZE 64
# define STEP_COUNTER_HEIGHT 80
# define WINDOW_HEIGHT (MAP_HEIGHT * TILE_SIZE + STEP_COUNTER_HEIGHT)
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif


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

	char	**map;
	int	map_width;
	int	map_height;

}	t_game;

/* render.c */
void    render_map(t_game *game);
void    render_tile(t_game *game, int x, int y);
void    update_changed_tiles(t_game *game);
void    render_steps_counter(t_game *game, int steps);

/* redraw,c */
void    redraw_all_collectibles(t_game *game);
void    redraw_door(t_game *game);
void    redraw_all_enemies(t_game *game);

/* player.c */
int     handle_keypress(int keycode, void *param);
void    handle_movement(t_game *game, int dx, int dy, void *player_img);
void    handle_death(t_game *game);
void    handle_collectibles(t_game *game);
void    handle_exit(t_game *game);

/* animation.c */
int     animated_game(void *param);
void    update_enemy_animation(t_game *game, int *redraw_enemies);
void    update_door_animation(t_game *game, int *rredraw_door);
void    update_collectibles_animation(t_game *game, int *redraw_collectibles);

/* load_images.c */
int     load_player_images(t_game *game);
int     load_collectibles_images(t_game *game);
int     load_number_images(t_game *game);
int     load_enemy_images(t_game *game);
int     load_door_images(t_game *game);

/* init.c */
int     init_game(t_game *game);
void    init_map(t_game *game);
void    count_collectibles(t_game *game);

/* cleanup.c */
void    cleanup_resources(t_game *game);

/* get_next_line */
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(char *str, char search_str);


void	read_map(const char *file_name, t_game *game);
void	check_file_extension(const char *filename);
void	validate_map_characters(t_game *game);
void    validate_map_elements(t_game *game);
void	validate_walls(t_game *game);
void    validate_path(t_game *game);
#endif
