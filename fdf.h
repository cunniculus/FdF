#ifndef FDF_H
# define FDF_H

#include <stdio.h>	// perror()
#include <string.h>	// strerror()
#include <stdlib.h> // exit()
#include <math.h>
#include "libft.h"

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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;



// isometric rotation matrix struct
typedef struct s_irot_matrix
{
	float	r1[3];
	float	r2[3];
	float	r3[3];
}	t_irot_matrix;

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


// my own minilibx structs
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_row_list
{
	int					*row;
	struct s_row_list	*next;
}	t_row_list;

void	plot (int x, int y);

// isometric_rotation
t_point	isometric_rotation(t_point *point);
void	init_rot_matrix(t_irot_matrix *rotation);
float	dot_product(float row[3], t_point *point);
t_point	rotation_transformation(t_irot_matrix rotation, t_point *point);

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

// normalize
t_list	**normalize(t_list **map);
t_point	max_coord_values(t_list	*list);
t_point	min_coord_values(t_list	*list);


#endif
