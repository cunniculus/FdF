/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:32:31 by guolivei          #+#    #+#             */
/*   Updated: 2022/10/14 15:33:47 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
