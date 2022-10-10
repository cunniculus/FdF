#include <math.h>
#include "fdf.h"

float	*isometric_rotation(float point[3], float rotated_point[3])

{
	t_irot_matrix	rotation;

	init_rot_matrix(&rotation);

	rotation_transformation(rotation, point, rotated_point);

	return (rotated_point);
}

float	*rotation_transformation(t_irot_matrix rotation, float point[3], float rotated_point[3])
{

	rotated_point[0] = dot_product(rotation.r1, point);
	rotated_point[1] = dot_product(rotation.r2, point);
	rotated_point[2] = dot_product(rotation.r3, point);

	return (rotated_point);
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

float	dot_product(float row[3], float point[3])
{
	int		i;
	float	dp;

	i = 0;
	dp = 0;
	while (i < 3)
	{
		dp += row[i] * point[i];
		i++;
	}
	return (dp);
}
