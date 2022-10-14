/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:04:03 by guolive           #+#    #+#             */
/*   Updated: 2022/10/13 22:01:08 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h>	// perror()
#include <string.h>	// strerror()
#include <stdlib.h> // exit()
#include <math.h>
#include <mlx.h>
#include "libft.h"


#ifndef SCALE 
# define SCALE 20
#endif

#ifndef TRANSLATION_X 
# define TRANSLATION_X 300
#endif

#ifndef TRANSLATION_Y 
# define TRANSLATION_Y 300
#endif

#ifndef ISOMETRIC_X_ANGLE 
# define ISOMETRIC_X_ANGLE 35.264
#endif

#ifndef ISOMETRIC_Y_ANGLE 
# define ISOMETRIC_Y_ANGLE 0
#endif

#ifndef ISOMETRIC_Z_ANGLE 
# define ISOMETRIC_Z_ANGLE 45
#endif

#ifndef ROTATION_STEP
# define ROTATION_STEP 2
#endif

#ifndef WIDTH
# define WIDTH 900
#endif

#ifndef HIGHT
# define HIGHT 900
#endif

#ifndef PADDING
# define PADDING 100
#endif

#define MLX_ERROR -1

typedef struct s_rotated_angle
{
	int	x;
	int y;
	int z;
}	t_rotated_angle;

typedef struct s_boundaries
{
	float	min_x;
	float	min_y;
	float	min_z;
	float	max_x;
	float	max_y;
	float	max_z;
}	t_boundaries;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_list	*map;
	t_list	*transformed_map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_boundaries	bounds;
}	t_data;
	

// isometric rotation matrix struct
typedef struct s_matrix
{
	float	r1[3];
	float	r2[3];
	float	r3[3];
}	t_matrix;

// transformed point
typedef struct	s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct	s_rounded_point
{
	int	x;
	int	y;
	int	z;
	int		color;
}	t_rounded_point;


enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	ESC = 65307,
	L_ARROW = 65361,
	U_ARROW = 65362,
	R_ARROW = 65363,
	D_ARROW = 65364,
	LETTER_A = 97,
	LETTER_S = 115
};

/*
typedef struct s_row_list
{
	int					*row;
	struct s_row_list	*next;
}	t_row_list;
*/
int	setup_mlx(t_data *mlx);

// linear transformation - matrix multiplication
float	dot_product(float row[3], t_point point);
t_point	transformation(t_matrix rotation, t_point point);

// rotations 
t_list	*rotation(t_list *map, int keycode);
t_rotated_angle	get_angle(t_rotated_angle angle, int keycode);
t_point isometric_rotation(t_point point);
t_point	step_rotation(t_point point, t_rotated_angle angle);
void	init_rot_matrix_x(t_matrix *rotation, float degrees);
void	init_rot_matrix_y(t_matrix *rotation, float degrees);
void	init_rot_matrix_z(t_matrix *rotation, float degrees);


// isometric_projection
t_point	isometric_projection(t_point *point);
void	print_point(t_point *point);
void	print_rounded_point(t_rounded_point *point);

//void	init_proj_matrix(t_proj_matrix *projection);
//t_point	projection_transformation(t_proj_matrix projection, t_point *point);

// read_file
t_list	*get_map(char *map_name, t_data *mlx);
t_list	*get_row(int fd, t_list **list);
int		get_row_size(char **row_str);
int		*make_row_int(char **row_str);
void	free_row(char **row);

// draw_line
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	redraw_expose(t_data *vars);
void	plot(t_data img, t_list *transformed_map);


//bresenham.c
void plot_line_high(int x0, int y0, int x1, int y1, t_data img);
void plot_line_low(int x0, int y0, int x1, int y1, t_data img);
void plot_line(int x0, int y0, int x1, int y1, t_data img);

// normalize
t_list	*normalize(t_list *map);
t_point	max_coord_values(t_list	*list);
t_point	min_coord_values(t_list	*list);

// scale
t_list  *scale(t_list *map, t_boundaries bound);
void	init_scale_matrix(t_matrix  *scale, float x_range, float y_range);

// translate
t_list	*translate(t_list *map);
t_boundaries	map_boundaries(t_list *list);
t_boundaries	min_coord(t_list *list, t_boundaries *bound);
t_boundaries	max_coord(t_list *list, t_boundaries *bound);

#endif