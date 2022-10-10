#include "libft.h"
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int		get_row(int fd);
int		get_row_size(char **row_str);
int		*make_row_int(char **row_str);
void	free_row(char **row);

int main(int argc, char **argv)
{
	int fd;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	get_row(fd);
	return (0);
}

int	get_row(int fd)
{
	char	*line;
	int		*row_int;
	//char	**row_str;

	line = get_next_line(fd);
	if (!line)
		return (0);
	while (get_row(fd))
	{
		if (ft_strchr(line, '\n'))
			ft_bzero(ft_strchr(line, '\n'), 1);
		row_int = make_row_int(ft_split(line, ' '));
		free(line);

		for(int i = 0; row_int[i] != INT_MIN; i++)
		   printf("%3d", row_int[i]);
		printf("\n");
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
