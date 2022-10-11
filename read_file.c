#include "libft.h"
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

#include "fdf.h"

#include <stdio.h>


int main(int argc, char **argv)
{
	int fd;
	t_list *list;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	list = NULL;
	get_row(fd, &list);
	if (!close(fd))
		return (-1);
	return (0);
}

int	get_row(int fd, t_list **list)
{
	char	*line;
	t_point	point;

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


		for(t_list *tmp = *list; tmp; tmp = tmp->next) // mudar para while
		{
			// printf("\nNew row: %d\n", i);
			// isometric transform
			int j = 0;
			for (int i = 0; ((int *) (tmp->content))[i] != INT_MIN; i++) // mudar para while
			{
				printf("%3d",((int *) (tmp->content))[i]);
				point.x = i; 
				point.y = j; 
				point.z = ((int *)tmp->content)[i]; 
				isometric_projection(&point);
			}
			j++;
			printf("\n");
		}

	ft_lstclear(list, free);
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
