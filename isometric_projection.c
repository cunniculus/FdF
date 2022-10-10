#include "fdf.h"
#include <stdio.h>


float	*isometric_projection(float point[3], float projection[3])
{
	float			rotated_point[3];
	t_proj_matrix	proj_matrix;

	isometric_rotation(point, rotated_point);
	print_point(rotated_point);

	init_proj_matrix(&proj_matrix);

	projection_transformation(proj_matrix, rotated_point, projection);
	print_point(projection);

	return (projection);

}

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

float	*projection_transformation(t_proj_matrix projection, float	point[3],\
		float proj[3])
{
	
	proj[0] = dot_product(projection.p1, point);
	proj[1] = dot_product(projection.p2, point);
	proj[2] = dot_product(projection.p3, point);

	return (proj);
}

int main()
{
	float point[3] = {1,2,3};
	float	projection[3];

	isometric_projection(point, projection);

}

void print_point(float projection[3])
{
	int i = 0;
	while(i < 3)
	{
		printf("%f\n", projection[i]);
		i++;
	}
}
