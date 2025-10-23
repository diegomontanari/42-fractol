# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmontana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 15:00:00 by dmontana          #+#    #+#              #
#    Updated: 2025/01/03 15:00:00 by dmontana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I includes -I libft -I mlx_linux

# Directories
SRCDIR = srcs
LIBFTDIR = libft
MLXDIR = mlx_linux

# Source files
SRCS = $(SRCDIR)/main.c \
	   $(SRCDIR)/fractal.c \
	   $(SRCDIR)/control.c \
	   $(SRCDIR)/make_fractal.c \
	   $(SRCDIR)/utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a

# Default target
all: $(NAME)

# Build the main executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11 -lm -o $(NAME)

# Build libft library
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# Build mlx library
$(MLX):
	$(MAKE) -C $(MLXDIR)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(MLXDIR) clean

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
