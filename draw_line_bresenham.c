#include "fdf.h"

t_list	*generate_points(t_list *map, t_point(*transformation)(t_point *));
t_list	*generate_rounded_points(t_list	*point_list);
t_list	*generate_image(t_data *mlx, t_point(*transformation)(t_point *));
t_list	*generate_rotated_image(t_data *mlx, t_point *(*transformation)(t_point *));
int		rotate_hook(int keycode, t_data *mlx);

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

int	print_key(int keycode)
{
	ft_printf("key %d pressed\n!", keycode);
	return (0);
}

int	close_win_key(int keycode, t_data *vars)
{
	ft_printf("key %d pressed\n!", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_image(vars->mlx_ptr, vars->img);
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		exit(0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	redraw_expose(t_data *vars)
{
	ft_printf("redraw ");
	
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		mlx;

	if (argc != 2)
		return (-2);
	if (!setup_mlx(&mlx))
		return (-3);
	// get map and store data in a list; each node, one row of the map; first node has bottom row
	mlx.map = NULL;
	printf("generate_image:  aqui ok\n");
	get_map(argv[1], &mlx);
	if (!(mlx.map))
		return (-3);
	printf("generate_image:  aqui ok\n");
	mlx.transformed_map = generate_image(&mlx, isometric_projection);

	/*
	// print test
	for(t_list *tmp = mlx.transformed_map; tmp; tmp = tmp->next)
		print_point((t_point *)tmp->content);
*/
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img, 0, 0);

	//printf("put_image_to_window ok\n");

	mlx_hook(mlx.win_ptr, ON_KEYDOWN, 1L<<0, close_win_key, &mlx);
	mlx_hook(mlx.win_ptr, ON_KEYDOWN, 1L<<0, print_key, &mlx);

	mlx_hook(mlx.win_ptr, ON_KEYDOWN, 1L<<0, rotate_hook, &mlx); 

	mlx_expose_hook(mlx.win_ptr, redraw_expose, &mlx);
	mlx_loop(mlx.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(mlx.mlx_ptr, mlx.img);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	ft_lstclear(&mlx.map, free);
	ft_lstclear(&mlx.transformed_map, free);
	//printf("acabou\n");
	return (0);
}

int	rotate_hook(int keycode, t_data *mlx)
{
	ft_printf("rotate");
	full_color_screen(*mlx, 0x0);  
	if (keycode == R_ARROW)
	{
		mlx->transformed_map = generate_rotated_image(mlx, rotation_x_right);
		
		for(t_list *tmp = mlx->transformed_map; tmp; tmp = tmp->next)
			print_point((t_point *)tmp->content);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	}
	else if (keycode == L_ARROW)
	{
		mlx->transformed_map = generate_rotated_image(mlx, rotation_x_left);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	}
	else if (keycode == U_ARROW)
	{
		mlx->transformed_map = generate_rotated_image(mlx, rotation_y_right);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	}
	else if (keycode == D_ARROW)
	{
		mlx->transformed_map = generate_rotated_image(mlx, rotation_y_left);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	}
	return (0);
}

t_list	*generate_rotated_image(t_data *mlx, t_point *(*transformation)(t_point *))
{
	t_list	*transformed_map;
	t_list	*tmp;

	tmp = mlx->transformed_map;
	while (tmp)
	{
		tmp->content = transformation((t_point *)tmp->content);	
		tmp = tmp->next;
	}
	transformed_map = normalize(mlx->transformed_map);
	transformed_map = generate_rounded_points(transformed_map);
	plot(*mlx, transformed_map);	
	ft_lstclear(&transformed_map, free);
	return (mlx->transformed_map);
}


t_list	*generate_image(t_data *mlx, t_point(*transformation)(t_point *))
{
	t_list	*transformed_map;

	printf("clear 2: OK\n");
	mlx->transformed_map = generate_points(mlx->map, transformation);
	printf("clear 2: OK\n");
	transformed_map = normalize(mlx->transformed_map);
	printf("clear 2: OK\n");
	transformed_map = generate_rounded_points(transformed_map);
	printf("clear 2: OK\n");
	plot(*mlx, transformed_map);	
	printf("clear 2: OK\n");
	ft_lstclear(&transformed_map, free);
	printf("clear 2: OK\n");
	return (mlx->transformed_map);
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
	t_list			*tmp;
	t_rounded_point	*point;
	int				j;

	rounded_list = NULL;
	j = 0;
	tmp = point_list;
	while (point_list)
	{
		point = malloc(sizeof (t_rounded_point));
		point->x = round(((t_point *)point_list->content)->x);
		point->y = round(((t_point *)point_list->content)->y);
		point->z = round(((t_point *)point_list->content)->z);
		//print_rounded_point(point);
		ft_lstadd_back(&rounded_list, ft_lstnew(point));
		point_list = point_list->next;
		j++;
	}
	ft_lstclear(&tmp, free);
	return (rounded_list);
}
int	setup_mlx(t_data *mlx)
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
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,\
			&mlx->line_length, &mlx->endian);
	return (42);
}
// bresenham
//
//

void	plot(t_data mlx, t_list *transformed_map)
{
	t_rounded_point point1;
	t_rounded_point	point2;
	t_list			*tmp;
	int total;
	int x;
	int	i;

	total = 0;
	x = 0;
	while (mlx.map)
	{
		x = 0;
		while (((int *)mlx.map->content)[x] != INT_MIN)
			x++;
		total += x;
		mlx.map= mlx.map->next;
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
			((t_rounded_point *)tmp->next->content)->y, mlx);
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
		plot_line(point1.x, point1.y, point2.x, point2.y, mlx);
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
