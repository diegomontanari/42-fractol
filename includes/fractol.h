#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include "../libft/libft.h"

# define WIDTH 			1200
# define HEIGHT			800
# define SCALE_LIMIT	50000000
# define SCALE_PRS		1.3
# define SCALE_ITER		3

# define ESC 			65307
# define SPACE_KEY 		32
# define W_KEY			119
# define A_KEY			97
# define S_KEY			115
# define D_KEY			100

# define UP_ARROW		65362
# define LEFT_ARROW		65361
# define DOWN_ARROW		65364
# define RIGHT_ARROW	65363

# define UP_SCROLL		0x04
# define DOWN_SCROLL	0x05

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct s_type
{
	int		type;
	int		depth;
	int		iteration;
	double	pixel_x;    // Current pixel x position (was: width)
	double	pixel_y;    // Current pixel y position (was: height)
	double	scale;      // Zoom scale factor
	double	offset_x;   // X offset in complex plane (was: xr)
	double	offset_y;   // Y offset in complex plane (was: yi)
	double	cr;         // Real part of constant (for Julia set)
	double	ci;         // Imaginary part of constant (for Julia set)
}				t_type;

typedef struct s_mlx
{
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*win;
	int		color;
}				t_mlx;

typedef struct s_fractol
{
	t_mlx	mlx;
	t_color	color;
	t_type	fractal;
	long	last_zoom_time;
}				t_fractol;

/* Main functions */
int		main(int argc, char **argv);
void	menu(void);
void	ft_init(t_fractol *fractol, char **av);
int		fractal_choice(t_fractol *fractol, char **av);
double	ft_atof(const char *str);

/* Types of fractal */
int		julia(t_fractol *fractol);
int		mandelbrot(t_fractol *fractol);
int		rabbit(t_fractol *fractol);
int		monster(t_fractol *fractol);

/* Drawing function */
void	random_colors(t_fractol *fractol);
void	put_pixel(t_fractol *fractol, int depth);
void	ft_string(t_fractol *f);
int		ft_draw(t_fractol *fractol);

/* Accessor functions */
t_fractol	**fractol_slot(void);
void		fractol_set(t_fractol *f);
t_fractol	*fractol_get(void);
int			*exit_flag_slot(void);

/* Control function */
int		key(int key, t_fractol *fractol);
void	zoom_in(int x, int y, t_fractol *f);
void	zoom_out(int x, int y, t_fractol *f);
int		mouse(int mouse, int x, int y, t_fractol *fractol);
int		close_window(t_fractol *fractol);
void	clean_exit(t_fractol *f, int exit_code);
void	handle_signal(int sig);
void	setup_signals(void);
int		poll_exit_hook(t_fractol *f);

#endif

