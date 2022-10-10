#include <math.h>
#include "fdf.h"

plot_line(int x0, int y0, int x1, int y1)
{
    if (abs(y1 - y0) < abs(x1 - x0))
	{
        if (x0 > x1)
            plot_line_low(x1, y1, x0, y0);
        else
            plot_line_low(x0, y0, x1, y1);
	}
    else
	{
        if y0 > y1
            plot_line_high(x1, y1, x0, y0);
        else
            plot_line_high(x0, y0, x1, y1);
	}
}

plot_line_low(int x0, int y0, int x1, int y1)
{
	dx = x1 - x0;
    dy = y1 - y0;
    yi = 1;
    if (dy < 0)
	{
        yi = -1;
        dy = -dy;
	}
    diff = (2 * dy) - dx;
    y = y0;
	x = x0;
	while (x < x1)
	{
        plot(x, y);
        if diff > 0
		{
            y = y + yi
            diff = diff + (2 * (dy - dx))
		}
        else
            diff = diff + 2*dy
	}
}

plot_line_high(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	xi;
	int	diff;

	dx = x1 - x0
    dy = y1 - y0
    xi = 1
    if (dx < 0)
	{
        xi = -1;
        dx = -dx;
	}
    diff = (2 * dx) - dy;
    x = x0;
	y = y0;
	while (y < y1)
	{
        plot(x, y);
        if (diff > 0)
		{
            x = x + xi;
            diff = diff + (2 * (dx - dy));
		}
        else
            diff = diff + 2*dx;
	}
}
