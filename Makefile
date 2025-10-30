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

→$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lbsd -o $@

# Build libft library
$(LIBFT):
→$(MAKE) -C $(LIBFTDIR)

# Build mlx library
$(MLX):
→$(MAKE) -C $(MLXDIR)

# Compile source files
%.o: %.c
→$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
→rm -f $(OBJS)
→$(MAKE) -C $(LIBFTDIR) clean
→$(MAKE) -C $(MLXDIR) clean

# Clean everything
fclean: clean
→rm -f $(NAME)
→$(MAKE) -C $(LIBFTDIR) fclean