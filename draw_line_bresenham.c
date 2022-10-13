#include "fdf.h"

t_list	*generate_points(t_list *map);
t_list	*generate_rounded_points(t_list	*point_list);
t_list	*generate_image(t_data *mlx);
t_list	*generate_rotated_image(t_data *mlx, t_point (*rotation)(t_point, t_rotated_angle));
int		key_hook(int keycode, t_data *mlx);
int		rotation_event(int keycode, t_data *mlx);

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

int	handle_no_event(void *data)
{

	/* This function needs to exist, but it is useless for the moment */
	return (*((int *)data));
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
	t_data			mlx;

	if (argc != 2)
		return (-2);
	if (!setup_mlx(&mlx))
		return (-3);
	printf("setup ok:  aqui ok\n");
	mlx.map = NULL;
	get_map(argv[1], &mlx);
	if (!(mlx.map))
		return (-3);
	printf("map: ok\n");
	mlx.transformed_map = generate_points(mlx.map);
	printf("generate_points: ok\n");
	generate_image(&mlx);
	printf("generate_image:  aqui ok\n");
	// print test
	// for(t_list *tmp = mlx.transformed_map; tmp; tmp = tmp->next)
	// 	print_point((t_point *)tmp->content);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img, 0, 0);

	//printf("put_image_to_window ok\n");

	mlx_loop_hook(mlx.mlx_ptr, &handle_no_event, &mlx);

	mlx_hook(mlx.win_ptr, ON_KEYDOWN, 1L<<0, key_hook, &mlx); 

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

int	key_hook(int keycode, t_data *mlx)
{
	ft_printf("key %d pressed\n!", keycode);
	full_color_screen(*mlx, 0x0);  
	if (keycode >= L_ARROW && keycode <= D_ARROW)
		rotation_event(keycode, mlx);
	else if (keycode == ESC)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	rotation_event(int keycode, t_data *mlx)
{
	if (keycode == R_ARROW)
	{
		mlx->transformed_map = generate_rotated_image(mlx, rotation_x_right);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	}
	else if (keycode == 65361)
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

t_list	*generate_rotated_image(t_data *mlx, t_point (*rotation)(t_point, t_rotated_angle))
{
	t_list	*transformed_map;
	t_list	*isometric;
	mlx->bounds = map_boundaries(mlx->transformed_map);
	isometric = step_rotation(mlx->transformed_map, isometric_rotation);
	transformed_map = step_rotation(isometric, rotation);
	transformed_map = scale(transformed_map, mlx->bounds);
	transformed_map = translate(transformed_map);
	transformed_map = generate_rounded_points(transformed_map);
	plot(*mlx, transformed_map);	
	ft_lstclear(&transformed_map, free);
	ft_lstclear(&isometric, free);
	return (mlx->transformed_map);
}


t_list	*generate_image(t_data *mlx)
{
	t_list	*transformed_map;

	mlx->bounds = map_boundaries(mlx->transformed_map);
	transformed_map = step_rotation(mlx->transformed_map, isometric_rotation);
	transformed_map = scale(transformed_map, mlx->bounds);
	/*
	mlx->bounds = map_boundaries(transformed_map);
	printf("Boundaries %5.1f %5.1f %5.1f %5.1f %5.1f %5.1f\n",\
	mlx->bounds.min_x, mlx->bounds.min_y, mlx->bounds.min_z, mlx->bounds.max_x, mlx->bounds.max_y, mlx->bounds.max_z);
	*/
	transformed_map = translate(transformed_map);
	transformed_map = generate_rounded_points(transformed_map);
	plot(*mlx, transformed_map);	
	ft_lstclear(&transformed_map, free);
	return (mlx->transformed_map);
}

t_list	*generate_points(t_list *map)
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

	rounded_list = NULL;
	point = NULL;
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
