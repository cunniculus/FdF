/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bresenham.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:04:10 by guolive           #+#    #+#             */
/*   Updated: 2022/10/14 12:30:32 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	full_color_screen(t_data img, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HIGHT)
		{
			my_mlx_pixel_put(&img, x, y, color);
			y++;
		}
		x++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}



int	main(int argc, char **argv)
{
	t_data			mlx;

	if (argc != 2)
		return (-2);
	if (!setup_mlx(&mlx))
		return (-3);
	if (!setup_map(&mlx, argv[1]))
		return (-4);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img, 0, 0);
	mlx_loop_hook(mlx.mlx_ptr, &handle_no_event, &mlx);
	mlx_hook(mlx.win_ptr, ON_KEYDOWN, 1L << 0, key_hook, &mlx);
	mlx_expose_hook(mlx.win_ptr, redraw_expose, &mlx);
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	ft_lstclear(&mlx.map, free);
	ft_lstclear(&mlx.transformed_map, free);
	return (0);
}

t_list	*generate_image(t_data *mlx, int keycode)
{
	t_list	*transformed_map;
	t_list	*isometric;

	isometric = NULL;
	transformed_map = rotation(mlx->transformed_map, 0);
	if (keycode)
	{
		isometric = transformed_map;
		transformed_map = rotation(isometric, keycode);
	}
	transformed_map = scale(transformed_map, mlx->bounds);
	transformed_map = translate(transformed_map);
	transformed_map = generate_rounded_points(transformed_map);
	plot(*mlx, transformed_map);
	ft_lstclear(&transformed_map, free);
	ft_lstclear(&isometric, free);
	return (mlx->transformed_map);
}

void	plot(t_data mlx, t_list *transformed_map)
{
	t_rpoint	point1;
	t_rpoint	point2;
	t_list		*tmp;
	int			total;
	int			x;
	int			i;
	int			j;

	total = 0;
	x = 0;
	while (mlx.map)
	{
		x = 0;
		while (((int *)mlx.map->content)[x] != INT_MIN)
			x++;
		total += x;
		mlx.map = mlx.map->next;
	}
	i = 1;
	tmp = transformed_map;
	while (tmp->next)
	{
		if (i != x)
		{
			plot_line((t_rpoint *)tmp->content, (t_rpoint *) \
			tmp->next->content, mlx);
			i++;
		}
		else
			i = 1;
		tmp = tmp->next;
	}
	tmp = transformed_map;
	i = 0;
	while (tmp->next)
	{
		point1.x = ((t_rpoint *)tmp->content)->x;
		point1.y = ((t_rpoint *)tmp->content)->y;
		j = i;
		while (x + i < total && j < x + i)
		{
			tmp = tmp->next;
			j++;
		}
		point2.x = ((t_rpoint *)tmp->content)->x;
		point2.y = ((t_rpoint *)tmp->content)->y;
		plot_line(&point1, &point2, mlx);
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
