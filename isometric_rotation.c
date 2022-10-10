#include <math.h>
#include "fdf.h"

t_point		isometric_rotation(t_point *point)

{
	t_irot_matrix	rotation;

	init_rot_matrix(&rotation);

	rotation_transformation(rotation, point);

	return (*point);
}

t_point	rotation_transformation(t_irot_matrix rotation, t_point *point)
{

	point->x = dot_product(rotation.r1, point);
	point->y = dot_product(rotation.r2, point);
	point->z = dot_product(rotation.r3, point);

	return (*point);
}

void	init_rot_matrix(t_irot_matrix *rotation)
{
	rotation->r1[0] = sqrt(0.5);
	rotation->r1[1] = 0;
	rotation->r1[2] = -rotation->r1[0];

	rotation->r2[0] = 1 / sqrt(6);
	rotation->r2[1] = 2 * rotation->r2[0];
	rotation->r2[2] = rotation->r2[0];

	rotation->r3[0] = sqrt(1.0/3);
	rotation->r3[1] = -rotation->r3[0];
	rotation->r3[2] = rotation->r3[0];
}

float	dot_product(float row[3], t_point *point)
{
	float	dp;

	dp = row[0] * point->x + row[1] * point->y + row[2] * point->z;
	return (dp);
}
