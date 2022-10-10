#include "mlx.h"
#include "mlx_int.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h> // exit()
#include <errno.h>

#ifndef WIDTH
# define WIDTH 900
#endif


#ifndef HIGHT 
# define HIGHT 900
#endif

#ifndef ESC
# define ESC 65307
#endif

#ifndef B
# define B 1
#endif
#ifndef G
# define G 256
#endif

#ifndef R
# define R 65536
#endif

#ifndef A
# define A 16777216
#endif

#ifndef PI
# define PI 3.141592654
#endif

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};


typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	void	*img;
}				t_vars;

int	deal_key(int key, void *param)
{
	if (!param)
		ft_putnbr_fd(key, 1);
	return (0);
}

int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	get_a(int argb)
{
	return ((argb >> 24) & 0xFF);
}

int	get_r(int argb)
{
	return ((argb >> 16) & 0xFF);
}

int	get_g(int argb)
{
	return ((argb >> 8) & 0xFF);
}

int	get_b(int argb)
{
	return (argb & 0xFF);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	// this calculation is obscure!!!
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	my_mlx_get_pixel_color(t_image img, int x, int y)
{
	char	*dst;

	// this calculation is obscure!!!
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int*) dst);
}


void full_color_screen(t_image img, int color)
{
	int x = 0;
	while (x < WIDTH)
	{
		int y = 0;
		while (y < HIGHT)
		{
			 my_mlx_pixel_put(&img, x, y, color);
			 y++;
		}
		x++;
	}
}

void centered_disc(t_image img, int color, int radius)
{
	int cx;
	int cy;

	cx = WIDTH / 2;
	cy = HIGHT / 2;
	int x = 0;
	while (x < WIDTH)
	{
		int y = 0;
		while (y < HIGHT)
		{
			int udisc = cy + sqrt(pow(radius, 2) - pow(x - cx, 2));
			int ldisc = cy - sqrt(pow(radius, 2) - pow(x - cx, 2));
			if (y < udisc && y > ldisc && fabs((double)x - cx) < radius)
				my_mlx_pixel_put(&img, x, y, color);
			 y++;
		}
		x++;
	}
}

int	close_win_key(int keycode, t_vars *vars)
{
	ft_printf("key %d pressed\n!", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	return (0);
}

int close_win_mouse(int button, int x, int y, t_vars *vars)
{
	ft_printf("mouse button: %d\n(%d, %d)", button, x, y);
	if (button == 1 && x == 0 && y == 0)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	return (0);
}

int	redraw_expose(t_vars *vars)
{
	ft_printf("redraw ");
	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_image	img;

	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		ft_printf("Error: %s\n", strerror(errno));
		return (-1);
	}

	vars.win = mlx_new_window(vars.mlx, WIDTH, HIGHT, "Hello world!");
	if (!vars.win)
	{
		free(vars.win);
		ft_printf("Error: %s\n", strerror(errno));
		return (-1);
	}

	img.img = mlx_new_image(vars.mlx, WIDTH, HIGHT);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_printf("bits_per_pixel:\t%d\nline_legnth:\t%d\nendian:\t\t%d\n", img.bits_per_pixel, img.line_length, img.endian);

	full_color_screen(img, create_argb(0, 0x7F, 0x8F, 0x3F));
	centered_disc(img, 0x00FFFFFF, 100);

	mlx_key_hook(vars.win, deal_key, (void *)0);
	
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	vars.img = img.img;
	mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, close_win_key, &vars);
	mlx_hook(vars.win, ON_MOUSEDOWN, 1L<<2, close_win_mouse, &vars);
	mlx_expose_hook(vars.win, redraw_expose, &vars);
	mlx_loop(vars.mlx);
	free(img.addr);
	return (0);
}

