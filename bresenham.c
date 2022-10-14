/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:05:02 by guolive           #+#    #+#             */
/*   Updated: 2022/10/14 16:49:00 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update1(int *diff, int delta[2], int *coord, int invert);
static void	update2(int *diff, int delta[2], int *coord, int invert);

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
	int	delta[2];
	int	yi;
	int	diff;
	int	x;
	int	y;

	delta[0] = point2->x - point1->x;
	delta[1] = point2->y - point1->y;
	yi = 1;
	if (delta[1] < 0)
	{
		yi = -1;
		delta[1] = -delta[1];
	}
	diff = (2 * delta[1]) - delta[0];
	y = point1->y;
	x = point1->x;
	while (x < point2->x)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
		update1(&diff, delta, &y, yi);
		x++;
	}
}

void	plot_line_high(t_rpoint *point1, t_rpoint *point2, t_data img)
{
	int	delta[2];
	int	xi;
	int	diff;
	int	x;
	int	y;

	delta[0] = point2->x - point1->x;
	delta[1] = point2->y - point1->y;
	xi = 1;
	if (delta[0] < 0)
	{
		xi = -1;
		delta[0] = -delta[0];
	}
	diff = (2 * delta[0]) - delta[1];
	x = point1->x;
	y = point1->y;
	while (y < point2->y)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
		update2(&diff, delta, &x, xi);
		y++;
	}
}

static void	update1(int *diff, int delta[2], int *coord, int invert)
{
	if (*diff > 0)
	{
		*coord = *coord + invert;
		*diff = *diff + (2 * (delta[1] - delta[0]));
	}
	else
		*diff = *diff + 2 * delta[1];
}

static void	update2(int *diff, int delta[2], int *coord, int invert)
{
	if (*diff > 0)
	{
		*coord = *coord + invert;
		*diff = *diff + (2 * (delta[0] - delta[1]));
	}
	else
		*diff = *diff + 2 * delta[0];
}
