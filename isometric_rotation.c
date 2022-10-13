#include <math.h>
#include "fdf.h"

t_point	isometric_rotation(t_point point, t_rotated_angle angle)
{
	t_matrix		rotation;
	t_point			transformed_point;

	init_rot_matrix_z(&rotation, angle.z);
	transformed_point = transformation(rotation, point);
	init_rot_matrix_x(&rotation, angle.x);
	transformed_point = transformation(rotation, transformed_point);
	return (transformed_point);
}

t_list	*step_rotation(t_list *map, t_point(*step_rot)(t_point, t_rotated_angle angle))
{
	t_list	*rotated;
	t_point	*point;
	static t_rotated_angle angle;
	
	angle = get_angle (angle, step_rot);
	printf("Angles: %4d %4d %4d\n", angle.x, angle.y, angle.z);
	rotated = NULL;
	point = NULL;
	while (map)
	{
		point = malloc(sizeof (t_point));
		*point = *((t_point *)map->content);
		*point = step_rot(*point, angle);
		ft_lstadd_back(&rotated, ft_lstnew(point));
		map = map->next;
	}
	return (rotated);
}

t_rotated_angle	get_angle(t_rotated_angle angle, t_point(*step_rot)(t_point, t_rotated_angle angle))
{
	if (step_rot == isometric_rotation)
	{
		angle.x = (angle.x + ISOMETRIC_X_ANGLE) % 360;
		angle.y = (angle.y + ISOMETRIC_Y_ANGLE) % 360;
		angle.z = (angle.z + ISOMETRIC_Z_ANGLE) % 360;
	}
	else if (step_rot == rotation_x_right)
		angle.x = (angle.x  + ROTATION_STEP) % 360;
	else if (step_rot == rotation_y_right)
		angle.y = (angle.y  + ROTATION_STEP) % 360;
	else if (step_rot == rotation_x_left)
		angle.x = (angle.x  - ROTATION_STEP) % 360;
	else if (step_rot == rotation_y_left)
		angle.y = (angle.y  - ROTATION_STEP) % 360;
	return (angle);
}

t_point	rotation_x_right(t_point point, t_rotated_angle angle)
{
	t_matrix	rotation;
	t_point		transformed_point;
	
	init_rot_matrix_x(&rotation, angle.x);
	transformed_point =  transformation(rotation, point);
	return (transformed_point);
}

t_point	rotation_x_left(t_point point, t_rotated_angle angle)
{
	t_matrix	rotation;
	t_point		transformed_point;
	
	init_rot_matrix_x(&rotation, angle.x);
	transformed_point =  transformation(rotation, point);
	return (transformed_point);
}

t_point	rotation_y_right(t_point point, t_rotated_angle angle)
{
	t_matrix	rotation;
	t_point		transformed_point;
	
	init_rot_matrix_y(&rotation, angle.y);
	transformed_point =  transformation(rotation, point);
	return (transformed_point);
}

t_point	rotation_y_left(t_point point, t_rotated_angle angle)
{
	t_matrix	rotation;
	t_point		transformed_point;
	
	init_rot_matrix_y(&rotation, angle.y);
	transformed_point =  transformation(rotation, point);
	return (transformed_point);
}

t_point	transformation(t_matrix matrix, t_point point)
{
	t_point	transformed_point;

	transformed_point.x = dot_product(matrix.r1, point);
	transformed_point.y = dot_product(matrix.r2, point);
	transformed_point.z = dot_product(matrix.r3, point);
	return (transformed_point);
}

void	init_rot_matrix_x(t_matrix	*rotation, float degrees)
{
	float angle;

	angle = 2*M_PI * degrees / 360;
	rotation->r1[0] = 1;
	rotation->r1[1] = 0;
	rotation->r1[2] = 0;

	rotation->r2[0] = 0;
	rotation->r2[1] = cos(angle);
	rotation->r2[2] = -sin(angle);

	rotation->r3[0] = 0;
	rotation->r3[1] = -rotation->r2[2];
	rotation->r3[2] = rotation->r2[1];
;
}

void	init_rot_matrix_y(t_matrix	*rotation, float degrees)
{
	float angle;

	angle = 2*M_PI * degrees / 360;
	rotation->r1[0] = cos(angle);
	rotation->r1[1] = 0;
	rotation->r1[2] = sin(angle);

	rotation->r2[0] = 0;
	rotation->r2[1] = 1;
	rotation->r2[2] = 0;

	rotation->r3[0] = -rotation->r1[2];
	rotation->r3[1] = 0;
	rotation->r3[2] = rotation->r1[0];
}

void	init_rot_matrix_z(t_matrix	*rotation, float degrees)
{
	float angle;

	angle = 2*M_PI * degrees / 360;
	rotation->r1[0] = cos(angle);
	rotation->r1[1] = -sin(angle);
	rotation->r1[2] = 0;

	rotation->r2[0] = -rotation->r1[1];
	rotation->r2[1] = rotation->r1[0];
	rotation->r2[2] = 0;

	rotation->r3[0] = 0;
	rotation->r3[1] = 0;
	rotation->r3[2] = 1;
}

float	dot_product(float row[3], t_point point)
{
	float	dp;

	dp = row[0] * point.x + row[1] * point.y + row[2] * point.z;
	return (dp);
}