/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:06:33 by guolive           #+#    #+#             */
/*   Updated: 2022/10/14 12:56:33 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "fdf.h"

static t_list	*get_row(int fd, t_list **list);
static int	*make_row_int(char **row_str);
static int	get_row_size(char **row_str);
static void	free_row(char **row);

t_list	*get_map(char *map_name, t_data *mlx)
{
	int		fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	mlx->map = get_row(fd, &(mlx->map));
	mlx->bounds.hight = ft_lstsize(mlx->map);
	mlx->bounds.width = 0;
	while (((int *)mlx->map->content)[mlx->bounds.width] != INT_MIN)
		mlx->bounds.width++;
	ft_printf("hight = %d\n", mlx->bounds.hight);
	if (!mlx->map)
		return (NULL);
	if (!close(fd))
		return (NULL);
	return (mlx->map);
}

static t_list	*get_row(int fd, t_list **list)
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

static int	*make_row_int(char **row_str)
{
	int	i;
	int	*row_int;
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

static int	get_row_size(char **row_str)
{
	int	size;

	size = 0;
	while (row_str[size])
		size++;
	return (size);
}

static void	free_row(char **row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		free(row[i]);
		i++;
	}
	free(row);
}
