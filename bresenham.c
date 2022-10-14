/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:05:02 by guolive           #+#    #+#             */
/*   Updated: 2022/10/13 23:27:40 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line(t_rpoint *point1, t_rpoint *point2, t_data img)
{
	if (abs(point2->y - point1->y) < abs(point2->x - point1->x))
	{
		if (point1->x > point2->x)
			plot_line_low(point2, point1, img);
		else
			plot_line_low(point1, point2, img);
	}
	else
	{
		if (point1->y > point2->y)
			plot_line_high(point2, point1, img);
		else
			plot_line_high(point1, point2, img);
	}
}

void	plot_line_low(t_rpoint *point1, t_rpoint *point2, t_data img)
{
	int	dx;
	int	dy;
	int	yi;
	int	diff;
	int	x;
	int	y;

	dx = point2->x - point1->x;
	dy = point2->y - point1->y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	diff = (2 * dy) - dx;
	y = point1->y;
	x = point1->x;
	while (x < point2->x)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
		if (diff > 0)
		{
			y = y + yi;
			diff = diff + (2 * (dy - dx));
		}
		else
			diff = diff + 2 * dy;
		x++;
	}
}

void	plot_line_high(t_rpoint *point1, t_rpoint *point2, t_data img)
{
	int	dx;
	int	dy;
	int	xi;
	int	diff;
	int	x;
	int	y;

	dx = point2->x - point1->x;
	dy = point2->y - point1->y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	diff = (2 * dx) - dy;
	x = point1->x;
	y = point1->y;
	while (y < point2->y)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
		if (diff > 0)
		{
			x = x + xi;
			diff = diff + (2 * (dx - dy));
		}
		else
			diff = diff + 2 * dx;
		y++;
	}
}
