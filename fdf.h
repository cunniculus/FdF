#ifndef FDF_H
# define FDF_H

#include <stdio.h>	// perror()
#include <string.h>	// strerror()
#include <stdlib.h> // exit()
#include <math.h>

//isometric rotation matrix struct
typedef struct s_irot_matrix
{
	float	r1[3];
	float	r2[3];
	float	r3[3];
}	t_irot_matrix;

//projection matrix struct
typedef struct	s_proj_matrix
{
	float	p1[3];
	float	p2[3];
	float	p3[3];
}	t_proj_matrix;


void	plot (int x, int y);

// isometric_rotation
float	*isometric_rotation(float point[3], float rotated_point[3]);
void	init_rot_matrix(t_irot_matrix *rotation);
float	dot_product(float row[3], float point[3]);
float	*rotation_transformation(t_irot_matrix rotation, float point[3], float rotated_point[3]);

// isometric_projection
float	*isometric_projection(float point[3], float projection[3]);
void	init_proj_matrix(t_proj_matrix *projection);
float	*projection_transformation(t_proj_matrix projection, float point[3], float proj[3]);
void	print_point(float projection[3]);

#endif
