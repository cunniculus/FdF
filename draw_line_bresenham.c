#include <mlx.h>
#include <math.h>
#include "fdf.h"

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
	t_window	mlx;
	t_data		img;
	t_list		*map;
	t_list		*transformed_map;
	t_point 	*point;
	t_list		*tmp;
	int			i;

	if (argc != 2)
		return (-2);
	if (!setup_mlx(&mlx, &img))
		return (-3);
	// get map and store data in a list; each node, one row of the map; first node has bottom row
	map = NULL;
	get_map(argv[1], &map);
	if (!map)
	{
		printf("ta vazio esse trem\n");
		return (-3);
	}

	// normalize values

	// transformation -> isometric projection
	transformed_map = NULL;
	tmp = map;
	int j = 0;
	while (tmp)
	{
		i = 0;
		while (((int *)tmp->content)[i] != INT_MIN)
		{
			// transform point 1
			point = malloc(sizeof (t_point));
			point->x = i;
			point->y = j;
			point->z = ((int *)tmp->content)[i];
			isometric_projection(point);

			// add point1 to list of transformed points
			ft_lstadd_back(&transformed_map, ft_lstnew(point));

			i++;
		}
		tmp = tmp->next;
		j++;
	}

	for (t_list *tmp1 = transformed_map; tmp1; tmp1 = tmp1->next)
		print_point((t_point *)tmp1->content);

	
	// normalize points
	normalize(&transformed_map);
	for (t_list *tmp1 = transformed_map; tmp1; tmp1 = tmp1->next)
		print_point((t_point *)tmp1->content);


	t_rounded_point point1, point2;
	int total = 0;
	tmp = map;
	int x = 0;
	while (tmp)
	{
		x = 0;
		while (((int *)tmp->content)[x] != INT_MIN)
			x++;
		total += x;
		tmp = tmp->next;
	}
	i = 1;
	tmp = transformed_map;
	while(tmp->next)
	{
		point1.x = round(((t_point *)tmp->content)->x);
		point1.y = round(((t_point *)tmp->content)->y);
		point2.x = round(((t_point *)tmp->next->content)->x);
		point2.y = round(((t_point *)tmp->next->content)->y);
		if (i != x)
		{
			plot_line(point1.x, point1.y, point2.x, point2.y, img);
			i++;
		}
		else 
			i = 1;
		tmp = tmp->next;
	}
	tmp = transformed_map;
	i = 0;
	while(tmp->next)
	{
		point1.x = round(((t_point *)tmp->content)->x);
		point1.y = round(((t_point *)tmp->content)->y);
		int j = i;
		while (x + i < total && j < x + i)
		{
			tmp = tmp->next;
			j++;
		}
		point2.x = round(((t_point *)tmp->content)->x);
		point2.y = round(((t_point *)tmp->content)->y);
		plot_line(point1.x, point1.y, point2.x, point2.y, img);
		i++;
		j = 0;
		tmp = transformed_map;
		while (j < i)
		{
			tmp = tmp->next;
			j++;
		}
	}
	

	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, 0, 0);
	mlx_loop(mlx.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(mlx.mlx_ptr, img.img);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	ft_lstclear(&map, free);
	ft_lstclear(&transformed_map, free);
	return (0);
}

int	setup_mlx(t_window *mlx, t_data *img)
{

	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HIGHT, "Hello world!");
	if (!mlx->win_ptr)
	{
		free(mlx->win_ptr);
		return (0);
	}
	img->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,\
			&img->line_length, &img->endian);
	return (42);
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

