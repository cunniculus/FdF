#include "fdf.h"
#include <stdio.h>


t_point	isometric_projection(t_point *point)
{
	//t_proj_matrix	proj_matrix;

	isometric_rotation(point);

	point->z = 0;
	/*
	t_matrix	rotation;
	init_rot_matrix_z(&rotation, 45);
	rotation_transformation(rotation, point);
	*/

	//init_proj_matrix(&proj_matrix);

	//projection_transformation(proj_matrix, point);
	//print_point(point);

	return (*point);

}

/*
void	init_proj_matrix(t_proj_matrix *projection)
{
	projection->p1[0] = 1;
	projection->p1[1] = 0;
	projection->p1[2] = 0;
	projection->p2[0] = 0;
	projection->p2[1] = 1;
	projection->p2[2] = 0;
	projection->p3[0] = 0;
	projection->p3[0] = 0;
	projection->p3[0] = 0;
}

t_point	projection_transformation(t_proj_matrix projection, t_point *point)
{
	
	point->x = dot_product(projection.p1, point);
	point->y = dot_product(projection.p2, point);
	point->z = dot_product(projection.p3, point);

	return (*point);
}
*/

/*
int main()
{
	float point[3] = {1,2,3};
	float	projection[3];

	isometric_projection(point, projection);
}
*/

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
