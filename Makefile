NAME		= cub3D

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -std=c17

# --- MiniLibX (Linux) ---
LIBMLX		= minilibx-linux
MLX_A		= $(LIBMLX)/libmlx.a
INCLUDES	= -Iincludes -I$(LIBMLX)
MLXFLAGS	= -L$(LIBMLX) -lmlx -lXext -lX11 -lm

SRCDIR		= srcs
OBJDIR		= objs
SRCS		= main.c window.c events.c render.c
OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)

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