/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolive <guolivei@student.42sp.org.br>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:05:02 by guolive           #+#    #+#             */
/*   Updated: 2022/10/13 21:05:04 by guolive          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line(int x0, int y0, int x1, int y1, t_data img)
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
