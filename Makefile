CC = cc

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -lXext -lX11

SRCS = Mandatory/cleanup.c Mandatory/find_path.c Mandatory/init.c Mandatory/load_images.c Mandatory/main.c Mandatory/parsing.c Mandatory/parsing_helpers.c Mandatory/player.c Mandatory/render.c

SRCSB = Bonus/animation.c Bonus/cleanup_bonus.c Bonus/find_path_bonus.c Bonus/init_bonus.c Bonus/load_images_bonus.c Bonus/main_bonus.c Bonus/parsing_bonus.c Bonus/parsing_helpers_bonus.c Bonus/player_bonus.c Bonus/redraw_bonus.c Bonus/render_bonus.c

OBJS = $(SRCS:.c=.o)

OBJSB = $(SRCSB:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

NAME = so_long

BONUS = .bns

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

$(BONUS): $(OBJSB)
	@touch $(BONUS)
	$(CC) $(CFLAGS) $(OBJSB) -L $(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJSB)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@rm -f $(BONUS)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJS) $(OBJSB)
.PHONY: all bonus clean fclean re
