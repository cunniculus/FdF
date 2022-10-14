/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:05:18 by guolivei          #+#    #+#             */
/*   Updated: 2022/10/14 12:17:39 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*generate_points(t_list *map);

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
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
			&mlx->line_length, &mlx->endian);
	return (42);
}


int	setup_map(t_data *mlx, char *filename)
{
	mlx->map = NULL;
	get_map(filename, mlx);
	if (!(mlx->map))
		return (0);
	mlx->transformed_map = generate_points(mlx->map);
	mlx->bounds = map_boundaries(mlx->transformed_map);
	generate_image(mlx, 0);
	return (1);
}

static t_list	*generate_points(t_list *map)
{
	t_list	*transformed_map;
	t_point	*point;
	int		x_coord;
	int		y_coord;

	transformed_map = NULL;
	y_coord = 0;
	while (map)
	{
		x_coord = 0;
		while (((int *)map->content)[x_coord] != INT_MIN)
		{
			point = malloc(sizeof (t_point));
			point->x = x_coord;
			point->y = y_coord;
			point->z = ((int *)map->content)[x_coord++];
			ft_lstadd_back(&transformed_map, ft_lstnew(point));
		}
		map = map->next;
		y_coord++;
	}
	return (transformed_map);
}

t_list	*generate_rounded_points(t_list	*point_list)
{
	t_list		*rounded_list;
	t_list		*tmp;
	t_rpoint	*point;

	rounded_list = NULL;
	point = NULL;
	tmp = point_list;
	while (point_list)
	{
		point = malloc(sizeof (t_rpoint));
		point->x = round(((t_point *)point_list->content)->x);
		point->y = round(((t_point *)point_list->content)->y);
		point->z = round(((t_point *)point_list->content)->z);
		ft_lstadd_back(&rounded_list, ft_lstnew(point));
		point_list = point_list->next;
	}
	ft_lstclear(&tmp, free);
	return (rounded_list);
}
