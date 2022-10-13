#include <math.h>
#include "fdf.h"

t_point		isometric_rotation(t_point *point)

{
	t_matrix	rotation;

	init_rot_matrix_z(&rotation, 45);
	transformation(rotation, point);
	init_rot_matrix_x(&rotation, 35.264);
	transformation(rotation, point);

	return (*point);
}

t_point		*rotation_x_right(t_point *point)
{
	t_matrix	rotation;
	
	//printf("Inside rotation_x: ok\n");
	init_rot_matrix_x(&rotation, 20);
	//printf("point before trnasform: ");
	//print_point(point);
	transformation(rotation, point);
	//printf("point AFTER trnasform: ");
	//print_point(point);
	return (point);
}

t_point		*rotation_x_left(t_point *point)
{
	t_matrix	rotation;
	
	//printf("Inside rotation_x: ok\n");
	init_rot_matrix_x(&rotation, -20);
	printf("point before trnasform: ");
	print_point(point);
	printf("%4.1f %4.1f %4.1f\n %4.1f %4.1f %4.1f\n %4.1f %4.1f %4.1f\n",\
	rotation.r1[0], rotation.r2[1], rotation.r3[2],\
	 rotation.r1[0], rotation.r2[1], rotation.r3[2],\
	 rotation.r1[0], rotation.r2[1], rotation.r3[2]);
	transformation(rotation, point);
	printf("point AFTER trnasform: ");
	print_point(point);
	return (point);
}
t_point		*rotation_y_right(t_point *point)
{
	t_matrix	rotation;
	
	//printf("Inside rotation_x: ok\n");
	init_rot_matrix_y(&rotation, 20);
	transformation(rotation, point);
	return (point);
}

t_point		*rotation_y_left(t_point *point)
{
	t_matrix	rotation;
	
	//printf("Inside rotation_x: ok\n");
	init_rot_matrix_y(&rotation, -20);
	transformation(rotation, point);
	return (point);
}

t_point	transformation(t_matrix matrix, t_point *point)
{
	point->x = dot_product(matrix.r1, point);
	point->y = dot_product(matrix.r2, point);
	point->z = dot_product(matrix.r3, point);
	return (*point);
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

float	dot_product(float row[3], t_point *point)
{
	float	dp;

	dp = row[0] * point->x + row[1] * point->y + row[2] * point->z;
	return (dp);
}