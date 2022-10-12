#include "fdf.h"

void plot_line_high(int x0, int y0, int x1, int y1, t_data img);
void plot_line_low(int x0, int y0, int x1, int y1, t_data img);
void plot_line(int x0, int y0, int x1, int y1, t_data img);
t_list	*generate_points(t_list *map, t_point(*transformation)(t_point *));
t_list	*generate_rounded_points(t_list	*point_list);
void	plot(t_data img, t_list *map, t_list *transformed_map);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	redraw_expose(t_window *vars)
{
	ft_printf("redraw ");
	
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window	mlx;
	t_data		img;
	t_list		*map;
	t_list		*transformed_map;

	if (argc != 2)
		return (-2);
	if (!setup_mlx(&mlx, &img))
		return (-3);
	// get map and store data in a list; each node, one row of the map; first node has bottom row
	map = NULL;
	get_map(argv[1], &map);
	if (!map)
		return (-3);

	transformed_map = generate_points(map, isometric_projection);
	normalize(&transformed_map);
	transformed_map = generate_rounded_points(transformed_map);
	plot(img, map, transformed_map);	

	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, 0, 0);
	mlx_expose_hook(mlx.win_ptr, redraw_expose, &mlx);
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
	mlx->img = img->img;
	return (42);
}
// bresenham
//
//

void	plot(t_data img, t_list *map, t_list *transformed_map)
{
	t_rounded_point point1;
	t_rounded_point	point2;
	t_list			*tmp;
	int total;
	int x;
	int	i;

	total = 0;
	x = 0;
	while (map)
	{
		x = 0;
		while (((int *)map->content)[x] != INT_MIN)
			x++;
		total += x;
		map = map->next;
	}

	i = 1;
	tmp = transformed_map;
	while(tmp->next)
	{
		if (i != x)
		{
			plot_line(((t_rounded_point *)tmp->content)->x,\
			((t_rounded_point *)tmp->content)->y,\
			((t_rounded_point *)tmp->next->content)->x,\
			((t_rounded_point *)tmp->next->content)->y, img);
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
		point1.x = ((t_rounded_point *)tmp->content)->x;
		point1.y = ((t_rounded_point *)tmp->content)->y;
		int j = i;
		while (x + i < total && j < x + i)
		{
			tmp = tmp->next;
			j++;
		}
		point2.x = ((t_rounded_point *)tmp->content)->x;
		point2.y = ((t_rounded_point *)tmp->content)->y;
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

}

t_list	*generate_points(t_list *map, t_point(*transformation)(t_point *))
{
	t_list	*transformed_map;
	t_point	*point;
	int		i;
	int		j;

	transformed_map = NULL;
	j = 0;
	while (map)
	{
		i = 0;
		while (((int *)map->content)[i] != INT_MIN)
		{
			point = malloc(sizeof (t_point));
			point->x = i;
			point->y = j;
			point->z = ((int *)map->content)[i++];
			transformation(point);
			ft_lstadd_back(&transformed_map, ft_lstnew(point));
		}
		map = map->next;
		j++;
	}
	return (transformed_map);
}

t_list	*generate_rounded_points(t_list	*point_list)
{
	t_list			*rounded_list;
	t_rounded_point	*point;
	int				j;

	rounded_list = NULL;
	j = 0;
	while (point_list)
	{
		point = malloc(sizeof (t_rounded_point));
		point->x = round(((t_point *)point_list->content)->x);
		point->y = round(((t_point *)point_list->content)->y);
		point->z = round(((t_point *)point_list->content)->z);
		ft_lstadd_back(&rounded_list, ft_lstnew(point));
		point_list = point_list->next;
		j++;
	}
	ft_lstclear(&point_list, free);
	return (rounded_list);
}
