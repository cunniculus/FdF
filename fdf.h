#ifndef FDF_H
# define FDF_H

#include <stdio.h>	// perror()
#include <string.h>	// strerror()
#include <stdlib.h> // exit()
#include <math.h>
#include "libft.h"
#include <mlx.h>

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

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
}	t_window;
	


// isometric rotation matrix struct
typedef struct s_matrix
{
	float	r1[3];
	float	r2[3];
	float	r3[3];
}	t_matrix;

// projection matrix struct
typedef struct	s_proj_matrix
{
	float	p1[3];
	float	p2[3];
	float	p3[3];
}	t_proj_matrix;

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
	ON_DESTROY = 17
};

typedef struct s_row_list
{
	int					*row;
	struct s_row_list	*next;
}	t_row_list;

int	setup_mlx(t_window *mlx, t_data *img);
/*
void	plot (int x, int y);
*/
// isometric_rotation
t_point	isometric_rotation(t_point *point);
void	init_rot_matrix_x(t_matrix *rotation, float degrees);
void	init_rot_matrix_y(t_matrix *rotation, float degrees);
void	init_rot_matrix_z(t_matrix *rotation, float degrees);
float	dot_product(float row[3], t_point *point);
t_point	rotation_transformation(t_matrix rotation, t_point *point);

// isometric_projection
t_point	isometric_projection(t_point *point);
void	print_point(t_point *point);
//void	init_proj_matrix(t_proj_matrix *projection);
//t_point	projection_transformation(t_proj_matrix projection, t_point *point);

// read_file
t_list	**get_map(char *map_name, t_list **list);
t_list	**get_row(int fd, t_list **list);
int		get_row_size(char **row_str);
int		*make_row_int(char **row_str);
void	free_row(char **row);

// draw_line
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	redraw_expose(t_window *vars);


//bresenham.c
void plot_line_high(int x0, int y0, int x1, int y1, t_data img);
void plot_line_low(int x0, int y0, int x1, int y1, t_data img);
void plot_line(int x0, int y0, int x1, int y1, t_data img);

// normalize
t_list	**normalize(t_list **map);
t_point	max_coord_values(t_list	*list);
t_point	min_coord_values(t_list	*list);


#endif
