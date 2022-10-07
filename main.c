#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <math.h>

#ifndef WIDTH
# define WIDTH 900
#endif


#ifndef HIGHT 
# define HIGHT 900
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


typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

int	deal_key(int key, void *param)
{
	if (!param)
		ft_putnbr_fd(key, 1);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// this calculation is obscure!!!
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	my_mlx_get_pixel_color(t_data data, int x, int y)
{
	char	*dst;

	// this calculation is obscure!!!
	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int*) dst);
}


void full_color_screen(t_data img, int color)
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

void centered_disc(t_data img, int color, int radius)
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

void disc(t_data img, int center[2], int color, int radius)
{
	int x = 0;
	while (x < WIDTH)
	{
		int y = 0;
		while (y < HIGHT)
		{
			int udisc = center[1] + sqrt(pow(radius, 2) - pow(x - center[0], 2));
			int ldisc = center[1] - sqrt(pow(radius, 2) - pow(x - center[0], 2));
			if (y < udisc && y > ldisc && fabs((double)x - center[0]) < radius)
				my_mlx_pixel_put(&img, x, y, color);
			 y++;
		}
		x++;
	}
}

void	line(t_data img, int p1[2], int p2[2], int color, int thickness)
{
	double	m;
	double	c;
	int		max;
	int		min;
	int		vertical;

	if (p2[0] == p1[0])
	{
		vertical = TRUE;
		max = p2[1];
		min = p1[1];
		if (p1[1] > p2[1])
		{
			max = p1[1];
			min = p2[1];
		}
	}
	else
	{
		vertical = FALSE;
		m = ((double) (p2[1] - p1[1])) / (p2[0] - p1[0]);
		c = p1[1] - m * p1[0];
		max = p2[0];
		min = p1[0];
		if (p1[0] > p2[0])
		{
			max = p1[0];
			min = p2[0];
		}
	}
	int x = 0;
	while (x < WIDTH)
	{
		int y = 0;
		while (y < HIGHT)
		{
			if (!vertical)
			{
				int line = m * x + c;
				if (y <= line + thickness / 2 && y >= line - thickness / 2\
					&& x <= max && x >= min)
					my_mlx_pixel_put(&img, x, y, color);
			}
			else if (x >= p1[0] - thickness / 2 && x <= p1[0] + thickness / 2\
					&& y <= max && y >= min)
			{
					my_mlx_pixel_put(&img, x, y, color);
			}
			y++;
		}
		x++;
	}
}


void circle(t_data img, int center[2], int color, int radius, int thickness)
{
	unsigned int prev_color;

	prev_color = my_mlx_get_pixel_color(img, center[0], center[1]);
	disc(img, center, color, radius);  
	disc(img, center, prev_color, radius - thickness);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	// mlx_init function initializes the connection between 
	// your software and the display.
	mlx = mlx_init();
	if (!mlx)
		return (-1);

	// creates a window
	mlx_win = mlx_new_window(mlx, WIDTH, HIGHT, "Hello world!");

	// creates an image
	img.img = mlx_new_image(mlx, WIDTH, HIGHT);

	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_printf("bits_per_pixel:\t%d\nline_legnth:\t%d\nendian:\t\t%d\n", img.bits_per_pixel, img.line_length, img.endian);
	

	full_color_screen(img, 0x00FF0000);
	centered_disc(img, 0x00FFFFFF, 100);
	int p1[2] = {WIDTH / 2, HIGHT / 2};
	int p2[2] = {WIDTH / 2 + 100, HIGHT / 2};
	line(img, p1, p2, 0x0000FF00, 5); 
	p2[0] = WIDTH / 2; 
	p2[1] = HIGHT / 2 - 100;
	line(img, p1, p2, 0x000000FF, 5); 
	p2[0] =  WIDTH / 2 - 100 * cos(PI/4); 
	p2[1] =  HIGHT / 2 + 100 * sin(PI/4); 
	line(img, p1, p2, 0x00000000, 5); 
	int center[2] = {100, 100};
	circle(img, center, 0x0000FFFF, 50, 2);
	// mlx_key_hook(mlx_win, deal_key, (void *)0);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	// allows events to be received: 
	// 		key is pressed;
	// 		mouse button is pressed
	// 		part of the windows should be re-drawn (expose)
	// mlx_loop never returns; when an event happens, it calls a
	// user-defined function associated with this event.
	// each event can be assigned to different functions.
	// each window can define a different fucntion for the same event
	//
	mlx_loop(mlx);

	return (0);
}

