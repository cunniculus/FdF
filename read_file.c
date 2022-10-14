/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolive <guolivei@student.42sp.org.br>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:06:33 by guolive           #+#    #+#             */
/*   Updated: 2022/10/13 21:06:35 by guolive          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

#include "fdf.h"

#include <stdio.h>

t_point	max_coord_values(t_list *list);
t_point	min_coord_values(t_list *list);

t_list *get_map(char *map_name, t_data *mlx)
{
	int fd;
	// t_list *tmp;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	//printf("file opened\n");
	mlx->map = get_row(fd, &(mlx->map));
	//printf("rows_ready\n");
	if (!mlx->map)
		return (NULL);
	t_list *tmp = mlx->map;
	int j=0;
	while (tmp)
	{
		// printf("\nNew row: %d\n", i);
	//	for (int i = 0; ((int *) (tmp->content))[i] != INT_MIN; i++) // mudar para while
	//		printf("%3d",((int *) (tmp->content))[i]);
		j++;
		tmp = tmp->next;
	//	printf("\n");
	}
	//	printf("number of rows: %d\n", j);
	if (!close(fd))
		return (NULL);
	//printf("%p\n", mlx->map);
	return (mlx->map);
}

t_list *get_row(int fd, t_list **list)
{
	char	*line;

	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			ft_bzero(ft_strchr(line, '\n'), 1);
		ft_lstadd_back(list, ft_lstnew(make_row_int(ft_split(line, ' '))));

		free(line);
	}

	return (*list);
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


t_list *normalize(t_list *map)
{
	t_point	min;
	t_point	max;
	t_point	*point;
	t_list *normalized;

	min = min_coord_values(map);
	max = max_coord_values(map);
	//printf("Inside normalize\n%5.1f %5.1f\n%5.1f %5.1f\n", min.x, min.y, max.x, max.y);
	//int i = 0;
	normalized = NULL;
	while (map)
	{
		//printf("Inside loop: %d\n", i);
		//i++;
		point = malloc(sizeof (t_point));
		//printf("alocation ok\n");
		if (max.x > min.x + 0.001)

		{
			point->x = PADDING + (((((t_point *)map->content)->x -\
					min.x) * (WIDTH - 2 * PADDING)) / (max.x - min.x));
		//printf("Inside loop if x: %d\n", i);
		}
		else
		{
			point->x = max.x;
		//printf("Inside loop else x: %d\n", i);
		}
		if (max.y > min.y + 0.001)
		{
			point->y= PADDING + (((((t_point *)map->content)->y -\
					min.y) * (WIDTH - 2 * PADDING)) / (max.y - min.y));
		//printf("Inside loop if y: %d\n", i);
		}
		else
		{
			point->y = max.y;
		//printf("Inside loop else y: %d\n", i);
		}
		point->z = 0;
		//printf("Inside loop points ok: %d\n", i);
		ft_lstadd_back(&normalized, ft_lstnew(point));
		//printf("Inside loop ft_lstadd_back: %d\n", i);
		map = map->next;
		//printf("Inside loop end: %d\n", i);
	}
	return (normalized);
}

t_point	max_coord_values(t_list *list)
{
	t_point	point;

	point.x = (float) INT_MIN;
	point.y = (float) INT_MIN;
	while (list)
	{
		if (((t_point *)list->content)->x > point.x)
			point.x = ((t_point *)list->content)->x;
		if (((t_point *)list->content)->y > point.y)
			point.y = ((t_point *)list->content)->y;
		list = list->next;
	}
	point.z = 0;
	return (point);
}

t_point	min_coord_values(t_list *list)
{
	t_point	point;

	point.x = (float) INT_MAX;
	point.y = (float) INT_MAX;
	while (list)
	{
		if (((t_point *)list->content)->x < point.x)
			point.x = ((t_point *)list->content)->x;
		if (((t_point *)list->content)->y < point.y)
			point.y = ((t_point *)list->content)->y;
		list = list->next;
	}
	point.z = 0;
	return (point);
}

