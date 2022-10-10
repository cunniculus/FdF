#include "libft.h"
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

#include "fdf.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	int	line_number;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	line_number = 0;
	get_row(fd, &line_number);
	if (!close(fd))
		return (-1);
	return (0);
}

int	get_row(int fd, int *n)
{
	char	*line;
	int		*row_int;
	t_point	point;

	line = get_next_line(fd);
	if (!line)
		return (0);
	while (get_row(fd, n))
	{
		if (ft_strchr(line, '\n'))
			ft_bzero(ft_strchr(line, '\n'), 1);
		row_int = make_row_int(ft_split(line, ' '));
		free(line);

		for(int i = 0; row_int[i] != INT_MIN; i++)
		{
			// printf("\nNew row: %d\n", i);
			// isometric transform
			point.x = i; 
			point.y = *n; 
			point.z = row_int[i]; 
			isometric_projection(&point);
			my_mlx_test(point);
		}
		
		(*n)++;
	}
	free(row_int);
	return (1);
}

int	*make_row_int(char **row_str)
{
	int	i;
	int *row_int;
	int	size;

	size = get_row_size(row_str);
	row_int = (int *)malloc (sizeof (int) * (size + 1));
	if (!row_int)
		return (NULL);
	row_int[size] = INT_MIN;
	i = 0;
	while (row_str[i])
	{
		row_int[i] = ft_atoi(row_str[i]);
		i++;
	}
	free_row(row_str);
	return (row_int);
}

int	get_row_size(char **row_str)
{
	int	size;

	size = 0;
	while (row_str[size])
		size++;
	return (size);
}

void free_row(char **row)
{
	int i;

	i = 0;
	while (row[i])
	{
		free(row[i]);
		i++;
	}
	free(row);
}
