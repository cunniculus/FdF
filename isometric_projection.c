#include "fdf.h"
#include <stdio.h>


t_point	isometric_projection(t_point *point)
{
	isometric_rotation(point);
	point->z = 0;
	return (*point);

}


void print_point(t_point *point)
{
	printf("%6.1f", point->x);
	printf("%6.1f", point->y);
	printf("%6.1f\n", point->z);
}

void print_rounded_point(t_rounded_point *point)
{
	printf("%5d", point->x);
	printf("%5d", point->y);
	printf("%5d\n", point->z);
}
