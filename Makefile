NAME		= cub3D

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -std=c17

# --- MiniLibX (Linux) ---
LIBMLX		= minilibx-linux
MLX_A		= $(LIBMLX)/libmlx.a
MLXFLAGS	= -L$(LIBMLX) -lmlx -lXext -lX11 -lm

# --- libft (archive pré-compilée) ---
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

INCLUDES	= -Isrcs -Iincludes -I$(LIBMLX) -I$(LIBFT_DIR)

SRCDIR		= srcs
OBJDIR		= objs
SRCS		= main.c window.c events.c render.c \
			  parsing.c parse_lines.c parse_element.c parse_color.c \
			  map_build.c map_check.c utils.c \
			  get_next_line.c get_next_line_utils.c \
			  raycasting.c texture.c player.c movement.c
OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

# Les objets GNL (qui redéfinissent ft_strlen/strdup/strchr/strjoin) sont
# placés AVANT $(LIBFT_A) : l'archive n'extrait alors pas ces membres,
# ce qui évite les erreurs de "multiple definition".
$(NAME): $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLXFLAGS) -o $(NAME)

$(MLX_A):
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "MiniLibX absente, clone depuis git..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(LIBMLX); \
	fi
	@$(MAKE) -C $(LIBMLX)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus