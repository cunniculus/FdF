#include <mlx.h>
#include <math.h>
#include "fdf.h"

#ifndef WIDTH
# define WIDTH 900
#endif

#ifndef HIGHT
# define HIGHT 900
#endif

#define MLX_ERROR -1

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void plot_line_high(int x0, int y0, int x1, int y1, t_data img);
void plot_line_low(int x0, int y0, int x1, int y1, t_data img);
void plot_line(int x0, int y0, int x1, int y1, t_data img);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_list	*map;

	if (argc != 2)
		return (-2);

	mlx = mlx_init();
	if (mlx == NULL)
		return (MLX_ERROR);
	mlx_win = mlx_new_window(mlx, WIDTH, HIGHT, "Hello world!");
	if (mlx_win == NULL)
	{
		free(mlx_win);
		return (MLX_ERROR);
	}
	img.img = mlx_new_image(mlx, WIDTH, HIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
				&img.endian);

	map = NULL;
	get_map(argv[1], &map);
	if (!map)
	{
		printf("ta vazio esse trem\n");
		return (-3);
	}


	plot_line(0,0, WIDTH, HIGHT, img); 

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(mlx, img.img);
	mlx_destroy_display(mlx);
	free(mlx);
	ft_lstclear(&map, free);
	return (0);
}


// bresenham
//
void plot_line(int x0, int y0, int x1, int y1, t_data img)
{
    if (abs(y1 - y0) < abs(x1 - x0))
	{
        if (x0 > x1)
            plot_line_low(x1, y1, x0, y0, img);
        else
            plot_line_low(x0, y0, x1, y1, img);
	}
    else
	{
        if (y0 > y1)
            plot_line_high(x1, y1, x0, y0, img);
        else
            plot_line_high(x0, y0, x1, y1, img);
	}
}

void plot_line_low(int x0, int y0, int x1, int y1, t_data img)
{
	int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
	{
        yi = -1;
        dy = -dy;
	}
    int diff = (2 * dy) - dx;
    int y = y0;
	int x = x0;
	while (x < x1)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
        if (diff > 0)
		{
            y = y + yi;
            diff = diff + (2 * (dy - dx));
		}
        else
            diff = diff + 2*dy;
		x++;
	}
}

void plot_line_high(int x0, int y0, int x1, int y1, t_data img)
{
	int	dx;
	int	dy;
	int	xi;
	int	diff;

	dx = x1 - x0;
    dy = y1 - y0;
    xi = 1;
    if (dx < 0)
	{
        xi = -1;
        dx = -dx;
	}
    diff = (2 * dx) - dy;
    int x = x0;
	int y = y0;
	while (y < y1)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
        if (diff > 0)
		{
            x = x + xi;
            diff = diff + (2 * (dx - dy));
		}
        else
            diff = diff + 2*dx;
		y++;
	}
}

