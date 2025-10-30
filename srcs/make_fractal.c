#include "../includes/fractol.h"
#include <math.h>
#include <stdint.h>

/* Increase the colors in the struct each time it's called. */
void	random_colors(t_fractol *fractol)
{
	fractol->color.r += 15;
	fractol->color.g += 41;
	fractol->color.b += 10;
}

/* Write a pixel using bits_per_pixel and line_length (safe for MLX) */
static void	put_pixel_raw(t_fractol *f, int x, int y, int r, int g, int b)
{
	char	*dst;
	int		bytes_per_pixel;
	int		line;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	bytes_per_pixel = f->mlx.bits_per_pixel / 8;
	line = f->mlx.line_length;
	dst = f->mlx.addr + (y * line + x * bytes_per_pixel);
	if (bytes_per_pixel >= 3)
	{
		dst[0] = (char)r;
		dst[1] = (char)g;
		dst[2] = (char)b;
	}
	if (bytes_per_pixel == 4)
		dst[3] = 0;
}

/* Function that places the color pixel in the image according to depth. */
void	put_pixel(t_fractol *fractol, int depth)
{
	int	r;
	int	g;
	int	b;
	int	x;
	int	y;

	x = (int)fractol->fractal.pixel_x;
	y = (int)fractol->fractal.pixel_y;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	if (depth == fractol->fractal.iteration)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else
	{
		r = ((int)(fractol->color.r + (depth * 2.42))) & 0xFF;
		g = ((int)(fractol->color.g + (depth * 3.52))) & 0xFF;
		b = ((int)(fractol->color.b + (depth * 4.65))) & 0xFF;
	}
	put_pixel_raw(fractol, x, y, r, g, b);
}

/* Function that writes information to the hud */
void	ft_string(t_fractol *f)
{
	char	*num;
	char	*str;

	num = ft_itoa(f->fractal.iteration);
	str = ft_strjoin("Number of iterations : ", num);
	mlx_string_put(f->mlx.mlx, f->mlx.win, 10, 5, 0xFFFFFF, str);
	free(num);
	free(str);
	num = ft_itoa((int)f->fractal.scale);
	str = ft_strjoin("Scale value : ", num);
	mlx_string_put(f->mlx.mlx, f->mlx.win, 10, 35, 0xFFFFFF, str);
	free(num);
	free(str);
}

/* Function that starts the calculation of the depth of the good fractal,
 sends it to the put_pixel and puts everything in the image. */
int	ft_draw(t_fractol *f)
{
	int depth;
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			f->fractal.pixel_x = (double)x;
			f->fractal.pixel_y = (double)y;
			if (f->fractal.type == 1)
				depth = julia(f);
			else if (f->fractal.type == 2)
				depth = mandelbrot(f);
			else if (f->fractal.type == 3)
				depth = rabbit(f);
			else
				depth = monster(f);
			put_pixel(f, depth);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
	ft_string(f);
	return (0);
}
