#include "libft.h"
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

#include "fdf.h"

#include <stdio.h>

t_point	max_coord_values(t_list *list);
t_point	min_coord_values(t_list *list);

t_list **get_map(char *map_name, t_list **list)
{
	int fd;
	t_list *tmp;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	list = get_row(fd, list);
	if (!list)
		return (NULL);
	printf("ta vazio essse trem\n");
	tmp = *list;
	while (tmp)
	{
		// printf("\nNew row: %d\n", i);
		int j = 0;
		for (int i = 0; ((int *) (tmp->content))[i] != INT_MIN; i++) // mudar para while
			printf("%3d",((int *) (tmp->content))[i]);
		j++;
		tmp = tmp->next;
		printf("\n");
	}
	if (!close(fd))
		return (NULL);
	return (list);
}

t_list **get_row(int fd, t_list **list)
{
	char	*line;

	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			ft_bzero(ft_strchr(line, '\n'), 1);
		ft_lstadd_front(list, ft_lstnew(make_row_int(ft_split(line, ' '))));

		free(line);
	}

	return (list);
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


t_list **normalize(t_list **map)
{
	t_point	min;
	t_point	max;
	t_list *tmp;

	min = min_coord_values(*map);
	max = max_coord_values(*map);
	tmp = *map;
	while (tmp)
	{
		((t_point *)tmp->content)->x = PADDING + (((((t_point *)tmp->content)->x - min.x) * \
					(WIDTH - 2 * PADDING)) / (max.x - min.x));
		((t_point *)tmp->content)->y = PADDING + (((((t_point *)tmp->content)->y - min.y) * \
					(WIDTH - 2 * PADDING)) / (max.y - min.y));
		tmp = tmp->next;
	}
	return (map);
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
