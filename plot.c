/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:32:31 by guolivei          #+#    #+#             */
/*   Updated: 2022/10/14 16:08:48 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_along_row(t_data mlx, t_list *map, int width)
{
	int	i;

	i = 1;
	while (map->next)
	{
		if (i != width)
		{
			plot_line((t_rpoint *)map->content, (t_rpoint *) \
			map->next->content, mlx);
			i++;
		}
		else
			i = 1;
		map = map->next;
	}
}

void	plot_along_column(t_data mlx, t_list *map, int width, int total)
{
	t_list		*tmp;
	int			i;
	int			j;
	t_rpoint	*point1;
	t_rpoint	*point2;

	i = 0;
	tmp = map;
	while (tmp->next)
	{
		point1 = (t_rpoint *)tmp->content;
		j = i;
		while (width + i < total && j < width + i)
		{
			tmp = tmp->next;
			j++;
		}
		point2 = (t_rpoint *)tmp->content;
		plot_line(point1, point2, mlx);
		i++;
		tmp = ft_lstinode(map, i);
	}
}

void	plot(t_data mlx, t_list *transformed_map)
{
	int			total;
	int			x;

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
	plot_along_row(mlx, transformed_map, x);
	plot_along_column(mlx, transformed_map, x, total);
}
